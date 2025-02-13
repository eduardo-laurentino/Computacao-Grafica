#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

#pragma warning(disable : 4996)

GLfloat angleX, angleY, rotTerra, rotLua, rotMarte, rotSol, idJupt;

typedef struct vertex
{
	float x;
	float y;
	float z;
} vertex;

typedef struct face
{
	int v1, v2, v3;
	int n1, n2, n3;
	int t1, t2, t3;
} face;

std::vector<face> faces;
std::vector<vertex> vertices;
std::vector<vertex> normals;
std::vector<vertex> textures;
GLuint idEarth;
GLuint idMars;
GLuint idSol;
GLuint idLua;

void loadObj(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Erro ao abrir o arquivo!\n");
		return;
	}

	while (1)
	{

		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0)
		{
			vertex v;
			fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z);
			vertices.push_back(v);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			vertex n;
			fscanf(file, "%f %f %f\n", &n.x, &n.y, &n.z);
			normals.push_back(n);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			vertex vt;
			fscanf(file, "%f %f\n", &vt.x, &vt.y);
			textures.push_back(vt);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			face f;
			fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &f.v1, &f.t1, &f.n1,
				   &f.v2, &f.t2, &f.n2, &f.v3, &f.t3, &f.n3);
			faces.push_back(f);
		}
	}
}

// Recebe o arquivo de imagem e retorna o id da textura
GLuint loadTGA(const char *filename)
{

	static GLubyte TGA_TYPE_HEADER[8] = {0, 0, 2, 0, 0, 0, 0, 0};
	GLuint width, height, format;

	GLubyte *data;

	FILE *file;
	file = fopen(filename, "rb");

	if (file == NULL)
	{
		printf("Arquivo de textura não encontrado!\n");
		return 0;
	}

	GLubyte type_header[8];
	if (fread(type_header, 1, sizeof(type_header), file) != sizeof(type_header))
	{
		printf("Problema ao ler cabeçalho do arquivo!\n");
		fclose(file);
		return 0;
	}

	if (memcmp(TGA_TYPE_HEADER, type_header, sizeof(type_header)) != 0)
	{
		printf("Tipo de arquivo TGA inválido!\n");
		fclose(file);
		return 0;
	}

	GLubyte image_header[10];
	if (fread(image_header, 1, sizeof(image_header), file) != sizeof(image_header))
	{
		printf("Problema ao ler formato da imagem!\n");
		fclose(file);
		return 0;
	}

	width = image_header[5] * 256u + image_header[4];
	height = image_header[7] * 256u + image_header[6];

	if ((width <= 0) || (height <= 0))
	{
		printf("Tamanho de arquivo inválido!\n");
		fclose(file);
		return 0;
	}

	GLubyte depth = image_header[8];
	switch (depth)
	{
	case 24:
		format = GL_RGB;
		break;
	case 32:
		format = GL_RGBA;
		break;
	default:
		printf("Canal de cor inválido!\n");
		fclose(file);
		return 0;
	}

	size_t pixel_size = depth / 8u;
	size_t data_size = width * height * pixel_size;
	data = (GLubyte *)malloc(data_size);
	if (!data)
	{
		printf("Erro ao alocar memória!\n");
		fclose(file);
		return 0;
	}

	if (fread(data, 1, data_size, file) != data_size)
	{
		printf("Erro ao ler dados da imagem!\n");
		free(data);
		fclose(file);
		return 0;
	}

	// TGA stores image data as BGR(A).
	for (size_t i = 0; i < data_size; i += pixel_size)
	{
		GLubyte temp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = temp;
	}

	fclose(file);

	GLuint idTextura;
	glGenTextures(1, &idTextura);
	glBindTexture(GL_TEXTURE_2D, idTextura);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
				 GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);

	return idTextura;
}

void renderSphere()
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faces.size(); ++i)
	{
		vertex *v1 = &vertices[faces[i].v1 - 1];
		vertex *v2 = &vertices[faces[i].v2 - 1];
		vertex *v3 = &vertices[faces[i].v3 - 1];

		vertex *n1 = &normals[faces[i].n1 - 1];
		vertex *n2 = &normals[faces[i].n2 - 1];
		vertex *n3 = &normals[faces[i].n3 - 1];

		vertex *t1 = &textures[faces[i].t1 - 1];
		vertex *t2 = &textures[faces[i].t2 - 1];
		vertex *t3 = &textures[faces[i].t3 - 1];

		glNormal3f(n1->x, n1->y, n1->z);
		glTexCoord2f(t1->x, t1->y);
		glVertex3f(v1->x, v1->y, v1->z);

		glNormal3f(n2->x, n2->y, n2->z);
		glTexCoord2f(t2->x, t2->y);
		glVertex3f(v2->x, v2->y, v2->z);

		glNormal3f(n3->x, n3->y, n3->z);
		glTexCoord2f(t3->x, t3->y);
		glVertex3f(v3->x, v3->y, v3->z);
	}
	glEnd();
}

void displayPersp(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(angleX, 1, 0, 0);
	glTranslatef(10, 0, 0);
	// glColor3f(0.0f, 0.5f, 0.0f);

	glPushMatrix(); // Matriz pai

	glPushMatrix(); // inicio matriz terra
	glRotatef(rotTerra, 0, 1, 0);
	glTranslatef(15, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, idEarth);
	renderSphere();

	glRotatef(rotLua, 0, 1, 0);
	glPushMatrix(); // inicio matriz lua
	glTranslatef(2, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glScalef(0.2, 0.2, 0.2);
	glBindTexture(GL_TEXTURE_2D, idLua);
	renderSphere();
	glPopMatrix(); // fim matriz lua
	glPopMatrix(); // fim matriz terra

	glPushMatrix(); // inicio matriz sol
	glRotatef(rotSol, 0, 1, 0);
	glTranslatef(0, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glScalef(10.0, 10.0, 10.0);
	glBindTexture(GL_TEXTURE_2D, idSol);
	renderSphere();
	glPopMatrix(); // fim matriz sol

	glPushMatrix(); // inicio matriz jupter
	glRotatef(idJupt, 0, 1, 0);
	glTranslatef(25, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glScalef(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, idJupt);
	renderSphere();
	glPopMatrix(); // fim matriz jupter

	glPushMatrix(); // inicio matriz marte
	glRotatef(rotMarte, 0, 1, 0);
	glTranslatef(20, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	glBindTexture(GL_TEXTURE_2D, idMars);
	renderSphere();
	glPopMatrix(); // fim matriz marte

	glPopMatrix(); // fim da matriz pai
	glutSwapBuffers();
}

void init()
{
	angleX = 0;
	angleY = 0;

	GLfloat posicaoLuz[4] = {0.0, 0.0, 50.0, 1.0};
	GLfloat luzAmbiente[4] = {50.25, 50.25, 50.25, 1.0};
	GLfloat luzDifusa[4] = {0.5, 0.5, 0.5, 1.0};
	GLfloat luzEspecular[4] = {0.9, 0.9, 0.9, 1.0};
	GLfloat especularidade[4] = {3.0, 1.0, 1.0, 1.0};

	GLint especMaterial = 50;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	loadObj("sphere.obj");
	idEarth = loadTGA("earth.tga");
	idMars = loadTGA("mars.tga");
	idSol = loadTGA("sun.tga");
	idLua = loadTGA("moon.tga");
	idJupt = loadTGA("jupter.tga");
}

void resize(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	GLfloat fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, fAspect, 0.1, 1000);
}

void keyboard(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		angleX -= 10;
		break;
	case GLUT_KEY_RIGHT:
		angleX += 10;
		break;
	case GLUT_KEY_UP:
		rotTerra -= 3;
		rotLua -= 8;
		rotMarte -= 1;
		rotSol -= 1;
		angleY -= 1;
		idJupt -= 0.8;
		break;
	case GLUT_KEY_DOWN:
		rotTerra += 3;
		rotLua += 8;
		rotMarte += 1;
		rotSol += 1;
		angleY += 1;
		idJupt += 0.8;
		break;
	case 32:
		angleX = 0;
		angleY = 0;
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Sistema Solar");
	glutDisplayFunc(displayPersp);
	glutReshapeFunc(resize);
	glutSpecialFunc(keyboard);
	init();

	glutMainLoop();
	return 0;
}
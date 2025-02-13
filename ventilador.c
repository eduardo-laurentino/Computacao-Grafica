
#include <GL/glut.h>


GLfloat fAspect;

//rotX e rotY controlam a rotação geral da cena
//rotHead controla a rotação geral do motor
//indica a direção do movimento
GLdouble rotX = 0, rotY = 0, rotHead = 0, rotBlade = 0, reverse = 0;



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //limpa a tela antes de desenhar

	glLineWidth(2);

    //rotacionam a cena com base nas setas do teclado
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);

	glColor3f(1.0f, 0.0f, 0.0f);

	// Base do ventilador (um cubo achatado e alongado no eixo XZ)
	glPushMatrix();
	{
		glScalef(10, 2, 10);
		glTranslatef(0.0, -6.5, 0.0);
		glutWireCube(1);
	}
	glPopMatrix();

	// Haste do ventilafor (um cubo alongado no eixo Y representando o suporte vertical)
	glPushMatrix();
	{
		glScalef(2, 10, 2);
		glTranslatef(0.0, -0.7, 0.0);
		glutWireCube(1);
	}
	glPopMatrix();

	glColor3f(0.0f, 0.0f, 1.0f);

	// Motor do ventilador (um cubo)
	glPushMatrix();
	{
		glRotatef(rotHead, 0, 1, 0);
		glTranslatef(0.0, 0.0, 0.0);
		glScalef(4, 4, 6);
		glRotatef(90, 0, 1, 0);
		glutWireCube(1);
	}
	glPopMatrix();

	// Ponta do motor (esfera na frente do motor)
	glPushMatrix();
	{
		glRotatef(rotHead, 0, 1, 0);
		glTranslatef(0.0, 0.0, 3.2);
		glutSolidSphere(0.5, 10, 8);
		
	}
	glPopMatrix();

	glColor3f(0.0f, 1.0f, 0.0f);

	// Hélices horizontais (um cubo achatado e longo no eixo X)
	glPushMatrix();
	{
		glRotatef(rotHead, 0, 1, 0);
		glRotatef(rotBlade, 0, 0, 1);
		glScalef(16, 2, 1);
		glTranslatef(0.0, 0.0, 3.8);
		glutWireCube(1);
	}
	glPopMatrix();

	// Hélices verticais
	glPushMatrix();
	{
		glRotatef(rotHead, 0, 1, 0);
		glRotatef(rotBlade, 0, 0, 1);
		glScalef(2, 16, 1);
		glTranslatef(0.0, 0.0, 3.8);
		glutWireCube(1);
	}
	glPopMatrix();

	glutSwapBuffers();
}

//configuração da câmera (projeção)
void configProjection(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, fAspect, 0.5, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
}

void resize(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;

	fAspect = (GLfloat)w / (GLfloat)h;

	configProjection();
}

//controles do teclado
void keyboard(unsigned char key, int x, int y)
{
    //limita a rotação do motor entre -60 e 60 graus
	if (rotHead > 60) {
		reverse = 0;
	}
	if (rotHead < -60) {
		reverse = 1;
	}

	switch (key)
	{
	case 27:
		exit(0);
		break;

	case 32:
		rotHead += reverse ? 1 : -1;
		rotBlade += 200;
		break;
		
	case 'z':
		rotHead += 5;
		break;
		
	case 'x':
		rotBlade += 500;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

//controles com setas do teclado
void specialkeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotX += 10;
		break;
	case GLUT_KEY_DOWN:
		rotX += 10;
		break;
	case GLUT_KEY_LEFT:
		rotY += 10;
		break;
	case GLUT_KEY_RIGHT:
		rotY -= 10;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Avaliação 02");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeys);
	glutMainLoop();
	return 0;
}
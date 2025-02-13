#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void display(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Define a cor de fundo da cena (cor usada para limpar o buffer de cor)
	glClear(GL_COLOR_BUFFER_BIT);//Inicializa o buffer de cores antes de ele ser alterado

	glMatrixMode(GL_MODELVIEW); //Informa que as operações seguintes serão executadas na matrix modelview
	glLoadIdentity(); //Carrega a matriz identidade

	// glPointSize(10); //Define quantos pixels representarão um vértice na tela
	// glBegin(GL_POINTS);{
	// 	glColor3f(0.0f, 1.0f, 1.0f);
	// 	glVertex2f(0, 0);

	// }glEnd();

	//parede frontal
	glLineWidth(5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.3, 0.4);
	glVertex2f(-1.0, 0.4);
	glVertex2f(-1.0, -0.3);
	glVertex2f(-0.3, -0.3);
	glEnd();


	//parede lateral
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(1.0, 0.4);
	glVertex2f(-0.3, 0.4);
	glVertex2f(-0.3, -0.3);
	glVertex2f(1.0, -0.3);
	glEnd();

	//teto frontal
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.3, 0.4);
	glVertex2f(-0.7, 0.8);
	glVertex2f(-1.0, 0.4);
	glEnd();

	//teto lateral
	glColor3f(0.5f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex2f(1.0, 0.4);
	glVertex2f(0.7, 0.8);
	glVertex2f(-0.7, 0.8);
	glVertex2f(-0.3, 0.4);
	glEnd();

	//janela 1
	glColor3f(0.3f, 0.1f, 0.4f);
	glBegin(GL_QUADS);
	glVertex2f(0.2, 0.1);
	glVertex2f(0.2, 0.3);
	glVertex2f(-0.2, 0.3);
	glVertex2f(-0.2, 0.1);
	glEnd();

	//janela 2
	glColor3f(0.3f, 0.1f, 0.4f);
	glBegin(GL_QUADS);
	glVertex2f(0.8, 0.1);
	glVertex2f(0.8, 0.3);
	glVertex2f(0.4, 0.3);
	glVertex2f(0.4, 0.1);
	glEnd();

	//porta
	glColor3f(0.3f, 0.1f, 0.4f);
	glBegin(GL_QUADS);
	glVertex2f(-0.45, -0.3);
	glVertex2f(-0.45, 0.2);
	glVertex2f(-0.9, 0.2);
	glVertex2f(-0.9, -0.3);
	glEnd();


	//calçada
	glColor3f(0.6f, 0.6f, 0.4f);
	glBegin(GL_QUADS);
	glVertex2f(-0.9, -0.3);
	glVertex2f(-0.99, -0.6);
	glVertex2f(-0.5, -0.6);
	glVertex2f(-0.45, -0.3);
	glEnd();

	//linhas da janela 1
	glColor3f(0.6f, 0.6f, 0.0f);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex2f(-0.2, 0.2);
	glVertex2f(0.2, 0.2);
	glVertex2f(0.0, 0.3);
	glVertex2f(0.0, 0.1);
	glEnd();


	//linhas da janela 2
	glColor3f(0.6f, 0.6f, 0.0f);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex2f(0.4, 0.2);
	glVertex2f(0.8, 0.2);
	glVertex2f(0.6, 0.3);
	glVertex2f(0.6, 0.1);
	glEnd();

	//maçaneta
	glColor3f(0.9f, 0.9f, 0.0f);
	glPointSize(6.0);
	glBegin(GL_POINTS);
	glVertex2f(-0.8, 0.0);
	glEnd();


	glFlush(); //Informa que as operações devem ser processadas imediatamente e exibidas na tela
}


/*Recebe um o comprimento (width) e altura (height) da janela em pixels.*/
void resize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;

	printf("Tam. janela: (%i,%i)\n", w, h);
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv); //Inicializa a OpenGL
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //Configura os modos de exibição (mais detalhes no futuro)
	glutInitWindowSize(500, 500); //Define o tamanho da janela em pixels
	glutInitWindowPosition(0, 0); //Define a posição inicial da janela
	glutCreateWindow("Primeiro Exemplo"); //Cria a janela especificando seu título
	glutDisplayFunc(display); //Especifica a função de rendering (exibe a cena no loop)
	glutReshapeFunc(resize); //Especifica função a ser executada quando a janela é redimensionada
	//glutKeyboardFunc(keyboard); //Especifica função a ser executada quando uma tecla é pressionada

	glutMainLoop(); //Executa o loop de renderização
	return 0;

}
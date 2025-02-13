
#include <GL/glut.h>
#include <stdlib.h>

int ombro = 0, cotovelo = 0;
float translacaox = 1.0, translacaoy = 1.0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glPushMatrix();
    glRotatef(ombro, 0.0, 0.0, 1.0);
    glColor3f(0.5, 0.0, 0.0);
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //glTranslatef(2.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(2.0, 0.0, 0.0);
    glRotatef(cotovelo, 0.0, 0.0, 1.0);
    glTranslatef(translacaox, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.5);
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, w / (h * 1.0), 1.0, 20.0);
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        ombro = (ombro + 3) % 90;
        translacaox = translacaox += 0.1;
        translacaoy = translacaoy += 0.2;
        glutPostRedisplay();
        break;
    case 'd':
        ombro = (ombro - 3) % 90;
        translacaox = translacaox -= 0.1;
        translacaoy = translacaoy -= 0.4;
        glutPostRedisplay();
        break;
    case 's':
        cotovelo = (cotovelo + 3) % 45;
        glutPostRedisplay();
        break;
    case 'w':
        cotovelo = (cotovelo - 3) % 45;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glClearColor(1, 1, 1, 1);
    glutMainLoop();
    return 0;
}
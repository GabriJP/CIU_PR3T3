/*
Prototipo de programa principal
ULPGC, EII, Creando Interfaces de Usuario
*/

#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

float gl_ancho = 2.0, gl_alto = 2.0, gl_cerca = -1.0f, gl_lejos = 5.0;
int w_ancho = 500, w_alto = 500;

bool rotando = false;
float sentido = 1.0f;
int pasos_segundo = 50;
int angulo_paso = 1;
GLfloat angulo = 0;

void InitGlew() {
    GLenum glew_init = glewInit();
    if (glew_init != GLEW_OK) {
        fprintf(stderr, "Error %s\n", glewGetErrorString(glew_init));
    } else {
        printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    }
}

void InitGL() {

    if (gl_ancho / w_ancho != gl_alto / w_alto) {
        fprintf(stderr, "La relación de aspecto no es correcta\n");
    }

    glClearColor(0.0, 0.0, 0.0, 0.0);
    // TO DO

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-gl_ancho / 2.0, gl_ancho / 2.0, -gl_alto / 2.0, gl_alto / 2.0, gl_cerca, gl_lejos); // espacio de trabajo
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(angulo, 0, 0, 1);
    glColor3f(1, 1, 0);
    glRectf(-0.5f, -0.5f, 0.5, 0.5);
    glFlush();
    glutSwapBuffers();
}

void Timer(int v) {
    if (rotando) {
        angulo += angulo_paso * sentido;
        if (angulo > 360) angulo -= 360;
        if (angulo < -360) angulo += 360;
        glutPostRedisplay();
    }
    glutTimerFunc((unsigned int) (1000 / pasos_segundo), Timer, v);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void Raton(int boton, int estado, int x, int y) {
#pragma clang diagnostic pop
    if (estado == GLUT_DOWN) {
        if (boton == GLUT_LEFT_BUTTON) {
            rotando = true;
            sentido += 2;
        } else if (boton == GLUT_RIGHT_BUTTON) {
            rotando = true;
            sentido -= 2;
        } else if (boton == GLUT_MIDDLE_BUTTON) {
            rotando = false;
        }
    }
}

void ReshapeSize(int ancho, int alto) {

    float dx = gl_ancho;
    float dy = gl_alto;

    dx *= (float) ancho / (float) w_ancho;
    dy *= (float) alto / (float) w_alto;

    glViewport(0, 0, ancho, alto); // utiliza la totalidad de la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-dx / 2.0, dx / 2.0, -dy / 2.0, dy / 2.0, gl_cerca, gl_lejos); // espacio de trabajo
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(w_ancho, w_alto);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutCreateWindow("OpenGL Práctica 3_3");
    InitGlew();
    InitGL();
    glutDisplayFunc(Display);
    glutReshapeFunc(ReshapeSize);
    glutMouseFunc(Raton);
    glutTimerFunc(100, Timer, 0);


    glutMainLoop();
    return 0;
}
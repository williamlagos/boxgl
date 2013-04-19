#include "graphic.h"

void init() // Called before main loop to set up the program
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
        glVertex3f(0.0, 0.0, -10.0);
        glVertex3f(1.0, 0.0, -10.0);
        glVertex3f(0.0, 1.0, -10.0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-0.1, 0.1, -float(h)/(10.0*float(w)), float(h)/(10.0*float(w)), 0.2, 9999999.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int start_graphic(int argc,char **argv)
{
    glutInit(&argc, argv); // Initializes glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Hello!");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    init();
    glutMainLoop();
}

#include "physics.h"
#include "graphic.h"
#include "elements.h"
#include "utils.h"

int main_window,counter = 0;
int width = 800;
int height = 600;
bool direction = true;
float x = 0.005f;
float y = 0.0f;
float z = 0.0f;

void reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glLoadIdentity();
}

void define_direction()
{
    world.Step(timeStep,1, positionIterations);
    b2Vec2 position = body->GetPosition();
    //printf("%3.2f - %3.2f",position.x,position.y);
    if(direction){ 
        x = 0.001f*position.x;
        y = 0.001f*position.y;
		//z = 0.001f;
    }else{
        x = -0.001f*position.x;
        y = -0.001f*position.y;
		//z = -0.001f;
    }
    counter = 0;
    direction = !direction;
}

void display ( void )
{
    //load_json("elements.json");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glTranslatef(x,y,z);  
    glColor3f(0.7,0.3,0.5); 
    glPointSize(10.0);
    glBegin(GL_QUADS);
	  glVertex3f(-0.9f,0.9f,0.0f);
      glVertex3f(0.9f,0.9f,0.0f);
      glVertex3f(0.9f,-0.9f,0.0f);
      glVertex3f(-0.9f,-0.9f,0.0f);
    glEnd();
    counter++;
    if(counter == 1000) define_direction();
    glFlush();
    //glutSwapBuffers();
}

void idle()
{
    /*static int prev_time = glutGet(GLUT_ELAPSED_TIME);
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    int elapsed_time = curr_time - prev_time;
    prev_time = curr_time;
    glutPostRedisplay();*/
}

void initGL(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glShadeModel(GL_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.5,0.5,0.5);
}

void initGLUT(int argc, char** argv)
{
    /*glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL); // display mode
    glutInitWindowSize(width,height);
    glutInitWindowPosition(0,0);
    main_window = glutCreateWindow("BoxGL");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);*/
}

int start_engine(int argc, char** argv)
{
    srand(time(0));
    //initGLUT(argc, argv);
    initGL();
    initBOX2D(&world);
    //glutMainLoop();
    return 0;
}

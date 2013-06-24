#include "physics.h"
#include "graphic.h"
#include "elements.h"
#include "utils.h"

GLFWwindow* window;
int width = 800;
int height = 600;
int counter = 0;

bool direction = true;
float x = 0.0005f;
float y = 0.0f;
float z = 0.0f;

void reshape(int w,int h)
{
	if (w == width && h == height) 
		glfwGetWindowSize(window,&width,&height);
	else glfwSetWindowSize(window,w,h);
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
}

void define_direction()
{
    world.Step(timeStep,1, positionIterations);
    b2Vec2 position = body->GetPosition();
    if(direction){ 
        x = 0.001f*position.x;
        y = 0.001f*position.y;
    }else{
        x = -0.001f*position.x;
        y = -0.001f*position.y;
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
}

void initGL(int argc,char** argv)
{
	if(argc > 2) reshape(atoi(argv[1]),atoi(argv[2]));
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void initGLFW(char* n)
{
	glfwInit(); window = 
	glfwCreateWindow(width,height,n,NULL,NULL);
    glfwMakeContextCurrent(window);
}	

int mainLoop()
{
	while(!glfwWindowShouldClose(window)){
		display();
		glfwPollEvents();
        glfwSwapBuffers(window);
		reshape(width,height);
    }
    glfwTerminate();
    return 0;
}

int start_engine(int argc, char** argv)
{
	char name[6] = "BoxGL";
    srand(time(0));
    initBOX2D(&world);
	initGLFW(name);
	initGL(argc,argv);
    return mainLoop();
}

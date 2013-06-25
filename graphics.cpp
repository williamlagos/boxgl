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

void draw_grid(void)
{
    glColor3f(0.7,0.3,0.5); 
    glPointSize(10.0);
    glColor3f(0.1,0.1,0.9); 	
	float xmin=-50.0, xmax=50.0, dx=5.0, x;
	float ymin=-50.0, ymax=50.0, dy=5.0, y;
	glBegin(GL_LINES);
	for(x=xmin; x<=xmax; x+=dx){
		for(y=ymin; y<=ymax; y+=dy){
			glVertex3f(x, ymin, 0.0);
			glVertex3f(x, ymax, 0.0);
			glVertex3f(xmin, y, 0.0);
			glVertex3f(xmax, y, 0.0);
		}
	}
	glEnd();
}

void initGL()
{
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void initGLFW(char* n)
{
	glfwInit(); window = 
	glfwCreateWindow(width,height,n,NULL,NULL);
    glfwMakeContextCurrent(window);
}	

void colorful_triangle()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
}

void animate_triangle()
{
	glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
	colorful_triangle();
}

int mainLoop()
{
	initGL();
	
	draw_grid();
	glPushMatrix();
	animate_triangle();
	glPopMatrix();
	
	glfwPollEvents();
	glfwSwapBuffers(window);
	reshape(width,height);
}

int start_engine(int argc, char** argv)
{
	char name[6] = "BoxGL";
	//initBOX2D(&world);
	initGLFW(name);
	if(argc > 2) reshape(atoi(argv[1]),atoi(argv[2]));
	while(!glfwWindowShouldClose(window)) mainLoop();
    glfwTerminate();
    return 0;
}

#include "physics.h"
#include "graphic.h"
#include "elements.h"
#include "utils.h"

#define PRESS(X) key == X && action == GLFW_PRESS

GLFWwindow* window;
int width = 800;
int height = 600;
float x = 0.0f;
float y = 0.0f;
float z = 1.0f;

void reshape(int w,int h)
{
	if (w == width && h == height) 
		glfwGetWindowSize(window,&width,&height);
	else glfwSetWindowSize(window,w,h);
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
}

void draw_cube()
{
	glBegin(GL_POLYGON); glColor3f( 1.0, 0.5, 0.0 );     
	  glVertex3f(  0.5, -0.5, -0.5 ); glVertex3f(  0.5,  0.5, -0.5 );
	  glVertex3f( -0.5,  0.5, -0.5 ); glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
	glBegin(GL_POLYGON); glColor3f(1.0,  1.0, 1.0 );
	  glVertex3f(  0.5, -0.5, 0.5 );	glVertex3f(  0.5,  0.5, 0.5 );
	  glVertex3f( -0.5,  0.5, 0.5 );	glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();
	glBegin(GL_POLYGON); glColor3f(  1.0,  0.0,  1.0 );
	  glVertex3f( 0.5, -0.5, -0.5 );	glVertex3f( 0.5,  0.5, -0.5 );
	  glVertex3f( 0.5,  0.5,  0.5 );	glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();
	glBegin(GL_POLYGON); glColor3f(   0.0,  1.0,  0.0 );
	  glVertex3f( -0.5, -0.5,  0.5 );	glVertex3f( -0.5,  0.5,  0.5 );
	  glVertex3f( -0.5,  0.5, -0.5 );	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
	glBegin(GL_POLYGON); glColor3f(   0.0,  0.0,  1.0 );
	  glVertex3f(  0.5,  0.5,  0.5 );	glVertex3f(  0.5,  0.5, -0.5 );
	  glVertex3f( -0.5,  0.5, -0.5 );	glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();
	glBegin(GL_POLYGON); glColor3f(   1.0,  0.0,  0.0 );
	  glVertex3f(  0.5, -0.5, -0.5 );	glVertex3f(  0.5, -0.5,  0.5 );
	  glVertex3f( -0.5, -0.5,  0.5 );	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
}

void draw_grid(void)
{
	float x,y;
    glColor3f(0.1,0.1,0.9);
	glBegin(GL_LINES);
	for(x = 0.0; x <= 1.0; x += 0.1){
		for(y = 0.0; y <= 1.0; y += 0.1){
			// Colunas da matriz
			glVertex3f(x,y,0.0);  glVertex3f(-x,y,0.0);
			glVertex3f(x,-y,0.0); glVertex3f(-x,-y,0.0);
			
			// Linhas da matriz
			glVertex3f(x,y,0.0);  glVertex3f(x,-y,0.0);
			glVertex3f(-x,y,0.0); glVertex3f(-x,-y,0.0);
		}
	}
	glEnd();
}

void draw_orthogrid(void)
{
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
	//2D Mode
	//glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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

void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods)
{
    if(PRESS(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window,GL_TRUE);
	else if(PRESS(GLFW_KEY_UP)) z += 0.1f;
	else if(PRESS(GLFW_KEY_DOWN)) z -= 0.1f;
	else if(PRESS(GLFW_KEY_LEFT)) y += 0.1f;
	else if(PRESS(GLFW_KEY_RIGHT)) y -= 0.1f;
	else if(PRESS(GLFW_KEY_LEFT_ALT)) x += 0.1f;
	else if(PRESS(GLFW_KEY_RIGHT_ALT)) x -= 0.1f;
}

void initGLFW(char* n,int argc,char** argv)
{
	glfwInit(); window = 
	glfwCreateWindow(width,height,n,NULL,NULL);
    glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window,key_callback);
	if(argc > 2) reshape(atoi(argv[1]),atoi(argv[2]));
}

void glfwMainLoop()
{
	while(!glfwWindowShouldClose(window)){
		initGL();
		gluLookAt(x,y,z,0.0,0.0,0.0,0.0,1.0,0.0);
		draw_grid();
		draw_cube();
		glPushMatrix();
		animate_triangle();
		glPopMatrix();
		
		glfwPollEvents();
		glfwSwapBuffers(window);
		reshape(width,height);
	}
}

int start_engine(int argc, char** argv)
{
	char name[6] = "BoxGL";
	//initBOX2D(&world);
	deformation_matrix(10,10);
	initGLFW(name,argc,argv);
	glfwMainLoop();
    glfwTerminate();
    return 0;
}

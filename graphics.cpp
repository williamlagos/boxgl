#include "physics.h"
#include "graphic.h"
#include "elements.h"
#include "utils.h"

#define PRESS(X) key == X && action == GLFW_PRESS

Mesh matrix[100][100];
GLFWwindow* window;
int width = 800, height = 600;
float x = 0.01f, y = -0.01f, z = 0.02f;
float cZ = 0.0f, cY = 0.0f, cX = 0.0f; 
float uZ = 0.0f, uY = 1.0f, uX = 0.0f;

void reshape(int w,int h)
{
	if (w == width && h == height) 
		glfwGetWindowSize(window,&width,&height);
	else glfwSetWindowSize(window,w,h);
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
}

void animate_wave(int detail)
{
	float i = .79f;
	float wave = .1f/(float)glfwGetTime();
	for(int count = 0; count < 100; count++){
		glTranslatef(0.0f,0.0f,-wave*i);
		glBegin(GL_POLYGON); glColor3f(1.0,i,0.0);     
		glVertex3f( i,-i,-.125f/i); glVertex3f( i, i,-.125f/i);
		glVertex3f(-i, i,-.125f/i); glVertex3f(-i,-i,-.125f/i);
		glEnd();
		i -= .01f;
		for(int aux = 0; aux < 100; aux++){
			i *= matrix[count][aux].mass;
			i *= matrix[count][aux].newtons;
			wave /= matrix[count][aux].deltatm;
			wave /= matrix[count][aux].kmol;
		}
	}
}

void draw_cube()
{
	float depth = 0.125f;
	float size = 0.8f;
	
	glBegin(GL_POLYGON); glColor3f(1.0,0.9,0.0);     
	  glVertex3f(  size, -size, -depth ); glVertex3f(  size,  size, -depth );
	  glVertex3f( -size,  size, -depth ); glVertex3f( -size, -size, -depth );
	glEnd();
	
	glBegin(GL_POLYGON); glColor3f(1.0,0.5,1.0);
	  glVertex3f(  size, -size, depth );	glVertex3f(  size,  size, depth );
	  glVertex3f( -size,  size, depth );	glVertex3f( -size, -size, depth );
	glEnd();
	glBegin(GL_POLYGON); glColor3f(1.0,0.0,1.0);
	  glVertex3f( size, -size, -depth );	glVertex3f( size,  size, -depth );
	  glVertex3f( size,  size,  depth );	glVertex3f( size, -size,  depth );
	glEnd();
	glBegin(GL_POLYGON); glColor3f(0.0,1.0,0.0);
	  glVertex3f( -size, -size,  depth );	glVertex3f( -size,  size,  depth );
	  glVertex3f( -size,  size, -depth );	glVertex3f( -size, -size, -depth );
	glEnd();
	glBegin(GL_POLYGON); glColor3f(0.0,0.0,1.0);
	  glVertex3f(  size,  size,  depth );	glVertex3f(  size,  size, -depth );
	  glVertex3f( -size,  size, -depth );	glVertex3f( -size,  size,  depth );
	glEnd();
	glBegin(GL_POLYGON); glColor3f(1.0,0.0,0.0);
	  glVertex3f(  size, -size, -depth );	glVertex3f(  size, -size,  depth );
	  glVertex3f( -size, -size,  depth );	glVertex3f( -size, -size, -depth );
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
			glVertex3f(x,ymin, 0.0);
			glVertex3f(x,ymax, 0.0);
			glVertex3f(xmin,y, 0.0);
			glVertex3f(xmax,y, 0.0);
		}
	}
	glEnd();
}

float video_ratio()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return width / (float) height;
}

void initGL()
{
	float ratio = video_ratio();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio,ratio,-1.f,1.f,1.f,-1.f);
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
	// Visao ocular da camera
	else if(PRESS(GLFW_KEY_W)) z += 0.01f;
	else if(PRESS(GLFW_KEY_S)) z -= 0.01f;
	else if(PRESS(GLFW_KEY_A)) y += 0.01f;
	else if(PRESS(GLFW_KEY_D)) y -= 0.01f;
	else if(PRESS(GLFW_KEY_Q)) x += 0.01f;
	else if(PRESS(GLFW_KEY_E)) x -= 0.01f;
	// Visao pela altura da camera
	else if(PRESS(GLFW_KEY_I)) uX += 0.01f;
	else if(PRESS(GLFW_KEY_K)) uX -= 0.01f;
	else if(PRESS(GLFW_KEY_J)) uY += 0.01f;
	else if(PRESS(GLFW_KEY_L)) uY -= 0.01f;
	else if(PRESS(GLFW_KEY_U)) uZ += 0.01f;
	else if(PRESS(GLFW_KEY_O)) uZ -= 0.01f;
	// Visao pelo centro de referencia
	else if(PRESS(GLFW_KEY_Z)) cX += 0.01f;
	else if(PRESS(GLFW_KEY_M)) cX -= 0.01f;
	else if(PRESS(GLFW_KEY_X)) cY += 0.01f;
	else if(PRESS(GLFW_KEY_N)) cY -= 0.01f;
	else if(PRESS(GLFW_KEY_C)) cZ += 0.01f;
	else if(PRESS(GLFW_KEY_B)) cZ -= 0.01f;
}

void initGLFW(char* n,int argc,char** argv)
{
	glfwInit(); window = 
	glfwCreateWindow(width,height,n,NULL,NULL);
    glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window,key_callback);
	glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);
	if(argc > 2) reshape(atoi(argv[1]),atoi(argv[2]));
}

void glfwMainLoop()
{
	while(!glfwWindowShouldClose(window)){
		initGL();
		gluLookAt(x,y,z,cX,cY,cZ,uX,uY,uZ);
		
		draw_grid();
		draw_cube();
		glPushMatrix();
		animate_wave(100);
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
	deformation_matrix(matrix);
	initGLFW(name,argc,argv);
	glfwMainLoop();
    glfwTerminate();
    return 0;
}

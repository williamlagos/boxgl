#include <GLFW/glfw3.h>
#ifndef __APPLE__
 #include <GL/gl.h>
 #include <GL/glu.h>
#else
 #include <OpenGL/gl.h>
 #include <OpenGL/glu.h>
#endif
#include <Box2D/Box2D.h>
#include <time.h>

extern GLFWwindow* window;
extern int main_window,width,height,counter;
extern float x,y,z;

void init();
void display();
void reshape(int w,int h);
int start_engine(int argc,char **argv);

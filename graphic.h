#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <time.h>

extern int main_window;
extern int width, height;
extern float x,y,z;

void init();
void display();
void reshape(int w, int h);
int start_graphic(int argc,char **argv);

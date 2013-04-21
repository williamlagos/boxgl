#include "physics.h"
#include "graphic.h"
#include "utils.h"

#undef main
#ifdef WIN32
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char **argv)
{
	//cout << "Starting engine..." << endl;
	start_engine(argc,argv);
	return 0;
}

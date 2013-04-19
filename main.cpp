#include "physics.h"
#include "graphic.h"
#include "utils.h"

int main(int argc, char **argv)
{
	cout << "Starting engine..." << endl;
	start_physics(argc,argv);
	start_graphic(argc,argv);
	return 0;
}

#include <JSON/libjson.h>
#include <fstream>

typedef struct {
	float mass;
	float kmol;
	int coordx;
	int coordy;
	int newtons;
	int deltatm;
} Mesh;

void load_json(const char* name);
void deformation_matrix(Mesh matrix[100][100]);
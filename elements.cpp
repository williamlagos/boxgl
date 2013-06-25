#include "elements.h"
using namespace std;

void deformation_matrix(Mesh matrix[100][100])
{
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			Mesh m;
			m.mass = 1.0;
			m.kmol = 1.0;
			m.coordx = i;
			m.coordy = j;
			m.newtons = 1;
			m.deltatm = 1;
			matrix[i][j] = m;
		}
	}
}

void load_json(const char* name)
{
	/*std::ifstream stream;
	stream.open("elements.json",ifstream::in);
	std::string line,buffer;
	if(stream.is_open()){
		while(stream.good()){
			getline(stream,line);
			buffer.append(line);
		}
		stream.close();
	}
	JSONNODE* node = json_parse_unformatted(buffer.c_str());
	JSONNODE_ITERATOR i = json_begin(node);
	while(i != json_end(node)){
		if(i == JSON_NULL) break;
		else if(json_type(*i) == JSON_NODE) continue;
		printf("%s",json_name(*i)); i++;
	}*/
}

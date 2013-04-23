#include "elements.h"
#include <iostream>
#include <string>
using namespace std;

void load_json(const char* name)
{
	std::ifstream stream;
	stream.open("C:\boxgl\Debug\elements.json",ifstream::in);
	cout << stream.fail() << endl;
	std::string buffer;
	if(stream.is_open()){
		cout << "ABC" << endl;
		while(stream.good()){
			getline(stream,buffer);
			printf(buffer.c_str());
		}
		stream.close();
	}
	/*if(!fs) puts("Arquivo aberto incorretamente");
	fs >> buffer;
	JSONNODE* node = json_parse(buffer.c_str());
    for(JSONNODE_ITERATOR i = json_begin(node); 
		i != json_end(node); ++i){
      if(i == JSON_NULL) break;
      else if (json_type(*i) == JSON_NODE) continue;
      json_char *node_name = json_name(*i);
	  printf(node_name);
      json_free(node_name);
    }*/
}
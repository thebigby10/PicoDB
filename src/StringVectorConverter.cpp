#ifndef STRINGVECTORCONVERTER // Include guard start
#define STRINGVECTORCONVERTER
#include "String.cpp"
#include "Map.cpp"
#include "Vector.cpp"
#include "FileHandler.cpp"
#include "Table.cpp"
#include <fstream>

class StringVectorConverter{
private:
	Vector<Map<String, String> > data_s; 
	Vector<Table> data_v; 
public:
	StringVectorConverter(Vector<Map<String, String> > data_s){
		this->data_s = data_s;
	}
	StringVectorConverter(Vector<Table> data_v){
		this->data_v = data_v;
	}

	Vector<Table> StringToVector(){

	}

	Vector<Map<String, String> > VectorToString(){

	}

};

#endif
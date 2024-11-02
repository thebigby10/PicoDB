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
	Vector<String> data_s; 
	Vector<Table> data_v; 
public:
	StringVectorConverter(Vector<String> data_s){
		this->data_s = data_s;
	}
	StringVectorConverter(Vector<Table> data_v){
		this->data_v = data_v;
	}

	Vector<Table> StringToVector(){

	}

	String VectorToString(){

	}

};

#endif
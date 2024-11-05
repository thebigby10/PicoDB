#ifndef STRINGVECTORCONVERTER // Include guard start
#define STRINGVECTORCONVERTER
#include "String.cpp"
//#include "Map.cpp"
#include "Vector.cpp"
#include "FileHandler.cpp"
#include "Table.cpp"
#include <fstream>


using namespace std;
class StringVectorConverter{
public:
	Vector<Vector<String>> stringToVector(String data, String delimiter){
		Vector<Vector<String>> table_cell_data;

		int start_pos = 0;
		int str_length = data.length();
		while (start_pos<str_length) {
			int end_pos = start_pos;
			while (end_pos != '\n') {
                	++end_pos;
			}

			// Extract a single line
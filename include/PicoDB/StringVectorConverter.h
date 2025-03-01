// should rename to serializer

#ifndef STRINGVECTORCONVERTER // Include guard start
#define STRINGVECTORCONVERTER
#include "String.h"
//#include "Map.cpp"
#include "Vector.h"
#include "FileHandler.h"
#include "Table.h"
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
			String line = data.substr(start_pos, end_pos - start_pos);
			Vector<String> line_data;

			size_t pos = 0;
            while ((pos = line.findSubstring(delimiter)) != -1) {
				line_data.push_back(line.substr(0, pos).trim());
				line = line.substr(pos + 1, line.length()-(pos+1));
                	}
                	line_data.push_back(line.trim()); // Last table after the last comma
			table_cell_data.push_back(line_data);

			// Move to the next line
			start_pos = end_pos + 1;

		}
        	return table_cell_data;
	}

    //used in saveTabl
	String vectorToString(Vector<String> vec_data) ;

	String vector2DToString(Vector<Vector<String>> vec_data, String delimiter) ;
};

#endif

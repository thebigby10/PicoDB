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
	Vector<Vector<String>> stringToVector(String data, String delimiter) {
		Vector<Vector<String>> table_cell_data;

		int start_pos = 0;
		int str_length = data.length();

		while (start_pos < str_length) {
			// Find the end of the current line
			int end_pos = start_pos;
			while (end_pos < str_length && data[end_pos] != '\n') {
				++end_pos;
			}

			// Extract a single line
			String line = data.substr(start_pos, end_pos - start_pos);
			Vector<String> line_data;

			// Split the line by the delimiter
			size_t pos = 0;
			while ((pos = line.findSubstring(delimiter)) != -1) {
				line_data.push_back(line.substr(0, pos).trim());
				line = line.substr(pos + delimiter.length(), line.length() - (pos + delimiter.length()));
			}

			// Add the last segment (after the last delimiter)
			if (line.length() > 0) {
				line_data.push_back(line.trim());
			}

			// Add the parsed line to the result
			table_cell_data.push_back(line_data);

			// Move to the next line
			start_pos = end_pos + 1;
		}

		return table_cell_data;
	}


    //used in saveTabl
	String vectorToString(Vector<String> vec_data) {
		String data;

		int n = vec_data.get_size();
		int j=0;
		//extract a single line from a 1D Vector
		for (j; j<n-1; j++) {
			data += vec_data[j];
			data += String(",");
		}
		data += vec_data[j]; // getting the last value and adding new line
		data += String("\n");
		return data;
	}

	String vector2DToString(Vector<Vector<String>> vec_data, String delimiter) {

		String data("");
		int num_rows = vec_data.get_size();
		int num_columns = 0;
		// if(vec_data.get_size()>0)
		// 	num_columns = vec_data[0].get_size();

		//extract a single line from a 1D Vector
		for (int i=0; i<num_rows; i++) {
			num_columns = vec_data[i].get_size();
            int j=0;
			if (j != num_columns-1) {
				for(j; j<num_columns-1; j++) {
                data += vec_data[i][j];
                data += String(delimiter);
            }
			data += vec_data[i][j];
			if (i!=num_rows-1) data += String("\n");
			} else {
				data += vec_data[i][j];
				if (i!=num_rows-1) data += String("\n");
			}
		}

		return data;
	}
};

#endif
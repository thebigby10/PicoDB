#include "../../include/PicoDB/StringVectorConverter.h"

//used in saveTabl
	String StringVectorConverter::vectorToString(Vector<String> vec_data) {
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

	String StringVectorConverter::vector2DToString(Vector<Vector<String>> vec_data, String delimiter) {

		String data("");
		int num_rows = vec_data.get_size();
		int num_columns = 0;
		if(vec_data.get_size()>0)
			num_columns = vec_data[0].get_size();

		//extract a single line from a 1D Vector
		for (int i=0; i<num_rows; i++) {
        int j=0;
        for(j; j<num_columns-1; j++) {
            data += vec_data[i][j];
            data += String(delimiter);
        }
			data += vec_data[i][j];
        data += String("\n");
		}

		return data;
	}

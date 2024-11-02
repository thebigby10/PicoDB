#ifndef STRINGVECTORCONVERTER // Include guard start
#define STRINGVECTORCONVERTER
#include "String.cpp"
#include "Map.cpp"
#include "Vector.cpp"
#include "FileHandler.cpp"
#include "Table.cpp"
#include <fstream>

using namespace std;
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

    Vector<Map<String, String>> VectorToString() {
        Vector<Map<String, String>> result; // Initialize result vector
        
        // Check if there are any tables to process
        for (size_t i = 0; i < data_v.get_size(); ++i) { // Iterate over each Table in data_v
            Table table = data_v[i];
            if (table.getSize() == 0) continue; // Skip empty tables
            
            // Get column names from the first row of the table
            Vector<String> headerRow = table.getRows()[0]; // Get the header row
            Vector<String> columns = table.getColumns();  // Get columns
 
            // Now iterate through the remaining rows
            for (size_t j = 1; j < table.getSize(); ++j) { // Start from 1 to skip the header
                Vector<String> row = table.getRows()[j]; // Get the current row
                Map<String, String> map; // Initialize a new map for the current row
                
                // Map each column name to the corresponding row value
                for (size_t k = 0; k < columns.get_size(); ++k) {
                    map[columns[k]] = row[k];
                }
                
                result.push_back(map); // Add the map to the result vector
            }
        }
        
        return result;
    }


};

#endif
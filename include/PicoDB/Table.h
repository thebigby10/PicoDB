#ifndef TABLE_H // Include guard start
#define TABLE_H
#include<iostream>
#include "String.h"
#include "Vector.h"
#include "Cell.h"

using namespace std;

/*
class Constraints{
public:
	String constraint_key; // NOT_NULL, UNIQUE, PEIMARY_KEY, FOREIGN_KEY, DEFAULT, CHECK
	String constraint_secondary_key; //LESS_THAN, GREATER_THAN, EQUAL_TO, NOT_EQUAL_TO, TABLE_NAME
	String constraint_value; // value or column name
};
*/

class Table{
private:
	String table_name;
	Vector<String> headers;
	Vector<String> data_types;
	Vector<String> constraints;
	Vector<Vector<Cell>> table_data;

	/*
		String constrain_key;
		// NOT_NULL, UNIQUE, PEIMARY_KEY, FOREIGN_KEY, DEFAULT, CHECK
		String constrain_secondary_key;
		//LESS_THAN, GREATER_THAN, EQUAL_TO, NOT_EQUAL_TO, TABLE_NAME
		String constrain_value;
		// value or column name
	*/

public:
    // Default constructor
    Table() : table_name(""), headers(), data_types(), constraints(), table_data() {}

	// new constructor - is used in createTable in picoDB class
	Table(String table_name, Vector<Vector<String>> col_data){
		this->table_name = table_name;
		extract_col_data(col_data);
	}

	//constructor overloader - is used in loadCurrentTables in Database class
	Table(String table_name, Vector<String> headers, Vector<String> data_types, Vector<String> constraints)
	: table_name(table_name), headers(headers), data_types(data_types), constraints(constraints){
	}

	// void extract_col_data(Vector<Vector<String>> temp_col_data) {
    //     int num_headers = temp_col_data.get_size();
	// 	for (int i=0; i<num_headers; i++) {
    //         this->headers.push_back(temp_col_data[i][0]);
    //         this->data_types.push_back(temp_col_data[i][1]);
    //         this->constraints.push_back(temp_col_data[i][2]);
    //     }
	// }

	//update table with new data
    void extract_col_data(Vector<Vector<String>> temp_col_data) {
        int num_headers = temp_col_data.get_size();
        for (int i = 0; i < num_headers; ++i) {
            if (temp_col_data[i].get_size() > 0) {
                headers.push_back(temp_col_data[i][0]);
            }
            if (temp_col_data[i].get_size() > 1) {
                data_types.push_back(temp_col_data[i][1]);
            }
            if (temp_col_data[i].get_size() > 2) {
                constraints.push_back(temp_col_data[i][2]);
            }
        }
    }


	// to update table cells
	void updateRecords (Vector<Vector<Cell>> cell_data) {
		this->table_data = cell_data;
	}

	void updateSingleRecord (Vector<Cell> cell_data) {
		this->table_data.push_back(cell_data);
	}

    // Getter for table_name
	String getTableName() const {
		return table_name;
	}

	// Getter for headers
	Vector<String> getHeaders() const {
		return headers;
	}

	// Getter for data_types
	Vector<String> getDataTypes() const {
		return data_types;
	}

	// Getter for constraints
	Vector<String> getConstraints() const {
		return constraints;
	}

	// Getter for table_data
	Vector<Vector<Cell>> getTableData() const {
		return table_data;
	}

	// set header
	void setHeaders(Vector<String> headers) {
		this->headers = headers;
	}

	// Additional methods for row management
	Vector<String> get_Row() {
		return headers;
	}

	int get_RowSize() {
		return table_data.get_size();
	}

};

#endif


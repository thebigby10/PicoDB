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
	Vector<String> get_Row();
	//needs to change?
	int get_RowSize();
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

	// void extract_col_data(Vector<Vector<String>> temp_col_data) ;

	//update table with new data
    void extract_col_data(Vector<Vector<String>> temp_col_data) ;


	// to update table cells
	void updateRecords (Vector<Vector<Cell>> cell_data) ;

	void updateSingleRecord (Vector<Cell> cell_data) ;

    // Getter for table_name
	String getTableName() const ;

	// Getter for headers
	Vector<String> getHeaders() const ;

	// Getter for data_types
	Vector<String> getDataTypes() const ;

	// Getter for constraints
	Vector<String> getConstraints() const ;

	// Getter for table_data
	Vector<Vector<Cell>> getTableData() const;

	// set header
	void setHeaders(Vector<String> headers);

};
#endif

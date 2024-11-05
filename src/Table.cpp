#ifndef TABLE_H // Include guard start
#define TABLE_H
#include<iostream>
#include "String.cpp"
#include "Vector.cpp"
#include "Cell.cpp"

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


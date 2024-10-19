#include<iostream>
#include "String.cpp"
#include "Vector.cpp"
#include "Cell.cpp"

using namespace std;

class Constrains{
public:
	String constrain_key; // NOT_NULL, UNIQUE, PEIMARY_KEY, FOREIGN_KEY, DEFAULT, CHECK
	String constrain_secondary_key; //LESS_THAN, GREATER_THAN, EQUAL_TO, NOT_EQUAL_TO, TABLE_NAME
	String constrain_value; // value or column name
}

class Table{
private:
	string table_name;
	vector<String> headers;
	vector<vector< Cell> > table_data;
	vector<Vector<String > >constrains;
	/*
		String constrain_key;
		// NOT_NULL, UNIQUE, PEIMARY_KEY, FOREIGN_KEY, DEFAULT, CHECK
		String constrain_secondary_key;
		//LESS_THAN, GREATER_THAN, EQUAL_TO, NOT_EQUAL_TO, TABLE_NAME
		String constrain_value;
		// value or column name
	*/
public:
//TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO
	Table(string table_name, vector<String >headers, String raw_data){ //add string conditions
		this->table_name = table_name;
		this->headers = headers;


	}
};
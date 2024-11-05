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
<<<<<<< HEAD
//TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO
	Table(string table_name, vector<String >headers, String raw_data){ //add string conditions
		this->table_name = table_name;
		this->headers = headers;


=======
	Table(string table_name, vector<int >rows){ //add string conditions
		this->table_name = table_name;
		for(int i = 0; i < rows.size(); ++i){
			vector<Cell> row;
			row.push_back(Cell(rows[i]));
			table_data.push_back(row);
		}
	}
	
	size_t getSize() const {
        return table_data.size();
    }
	vector<string> getColumns() const {
		vector<string> columns;
		if (table_data.size() > 0) {
			for (size_t i = 0; i < table_data[0].size(); ++i) {
				columns.push_back("Column " + to_string(i + 1));
			}
		}
		return columns;
	}
	vector<vector<Cell> > getRows() const {
		return table_data;
>>>>>>> rafi-dev
	}
};
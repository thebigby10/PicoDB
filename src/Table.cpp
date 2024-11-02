#include<iostream>
#include<string>
#include<vector>
#include "Cell.cpp"

using namespace std;

class Table{
private:
	string table_name;
	vector<vector< Cell> > table_data;
public:
	Table(string table_name, vector<int >rows){ //add string conditions
		this->table_name = table_name;
		for(int i = 0; i < rows.size(); ++i){
			vector<Cell> row;
			row.push_back(Cell(rows[i]));
			table_data.push_back(row);
		}


	}
	 getrows(){
		return table_data;
	}
};
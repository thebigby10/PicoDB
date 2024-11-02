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
	}
};
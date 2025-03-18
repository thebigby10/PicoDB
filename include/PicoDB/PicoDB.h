#include<iostream>

#include "Database.h"
#include "Table.h"
#include "Cell.h"

#include "FileHandler.h"
#include "Encryptor.h"

#include "Vector.h"
// #include "Date.h"

#include "String.h"
//#include "Map.h"

class PicoDB{
public:
	Database db;

public:
	PicoDB(String db_name, String db_path, String username, String key, String table_delimiter)
		: db(db_name, db_path, username, key, table_delimiter) {
			// Constructor body can remain empty if no additional setup is needed
	}

	PicoDB(String db_name, String db_path, String username, String key)
	: db(db_name, db_path, username, key) {
			// No additional setup implemented in the constructor body yet
	}

	bool createTable(String table_name, Vector<Vector<String>> col_data){
		this->db.get_tables().push_back(Table(table_name, col_data));
		return true;
	}

	// void select(String table_name, Vector<String> cols){
	// 	if(cols.get_size()==0){
	// 		Table input_table;
	// 		for(int i=0;i<db.get_tables().get_size();i++){
	// 			if((db.get_tables()[i].getTableName()) == (table_name)){
	// 				input_table = db.get_tables()[i];
	// 				break;
	// 			}
	// 		}
	// 		db.printTable(input_table);
	// 	}
	// }

	// bool insertInto(String table_name, Vector<String> col_data, Vector<String> col_values){
	// 	return this->db.insertInto(table_name, col_data, col_values);
	// }
bool insertInto(String table_name, Vector<String> col_names, Vector<String> values) {
    for (int i = 0; i < db.get_tables().get_size(); ++i) {
        if (db.get_tables()[i].getTableName() == table_name) {
            Table& table = db.get_tables()[i];
            // Ensure the number of columns matches the number of values
            if (col_names.get_size() == values.get_size()) {
                Vector<Cell> row_data;
                for (int j = 0; j < values.get_size(); ++j) {
                    // Convert values to Cell objects based on data type
                    // Assuming all values are strings for simplicity
                    row_data.push_back(Cell(values[j]));
                }
                table.updateSingleRecord(row_data);
            } else {
                std::cerr << "Column count does not match value count" << std::endl;
                return false;
            }
            return true;
        }
    }
    std::cerr << "Table not found" << std::endl;
    return false;
}


	/*
	vector<vector< string > > selectData(string table_name, vector<string> cols){

	}

	vector<vector< string > > selectDataWhere(string table_name, vector<string> cols){

	}*/

	bool saveDB(){
		this->db.saveDB();
		return true;
	}
	/*
	bool dropTable(){

	}
	*/
	Table select(String table_name, Vector<String> cols, String condition){
	   return this->db.select(table_name, cols, condition);
	}
	void printTable(Table& table){
	      this->db.printTable(table);
	}
// Add these to your PicoDB class
// String getDBName() const {
// 	return db.get_db_name();
// }

Vector<Table>& getTables() {
	return db.get_tables();
}

// inner join
Table innerJoin(String leftTableName, String rightTableName, String leftColumnFull, String rightColumnFull, Vector<String> selectedColumns) {
    Vector<Table>& tables = this->db.get_tables();
    Table leftTable, rightTable;
    bool leftFound = false, rightFound = false;

    for (int i = 0; i < tables.get_size(); i++) {
        if (tables[i].getTableName() == leftTableName) {
            leftTable = tables[i];
            leftFound = true;
        }
        if (tables[i].getTableName() == rightTableName) {
            rightTable = tables[i];
            rightFound = true;
        }
    }

    if (!leftFound || !rightFound) {
        std::cerr << "One or both tables not found!" << std::endl;
        return Table(); // Return empty table
    }

    // Extract column names without table prefixes
    String leftColumn = leftColumnFull;
    String rightColumn = rightColumnFull;
    
    int leftDotPos = leftColumnFull.find('.');
    int rightDotPos = rightColumnFull.find('.');
    
    if (leftDotPos != -1) {
        leftColumn = leftColumnFull.substr(leftDotPos + 1, leftColumnFull.length() - leftDotPos - 1);
    }
    
    if (rightDotPos != -1) {
        rightColumn = rightColumnFull.substr(rightDotPos + 1, rightColumnFull.length() - rightDotPos - 1);
    }
    
    return leftTable.innerJoin(rightTable, leftColumn, rightColumn, selectedColumns);

}



};

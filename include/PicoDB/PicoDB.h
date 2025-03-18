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

	// bool createTable(String table_name, Vector<Vector<String>> col_data){
	// 	this->db.get_tables().push_back(Table(table_name, col_data));
	// 	return true;
	// }

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

    bool createTable(String table_name, Vector<Vector<String>> col_data){
		return this->db.createTable(table_name, col_data);
    }
    // Table select(Table table, Vector<String> cols, String condition) {
    //     return this->db.select(table, cols, condition);
    // }

    Table getTable(String table_name){
        return this->db.get_table_by_name(table_name);
    }

    // bool dropTable(const String& table_name) {
    //     return this->dropTable(table_name);

    Table select(Table table_name, Vector<String> cols, String condition) {
        return this->db.select(table_name, cols, condition);
    }

    bool update(String table_name, Vector<Vector<String>> update_values, String condition) {
        return this->db.update(table_name, update_values, condition);
    }

    bool deleteFrom(String table_name, String condition) {
        return this->db.deleteFrom(table_name, condition);
    }

    bool insertInto(String table_name, Vector<String> col_names, Vector<String> values) {
        return this->db.insertInto(table_name, col_names, values);
    }

	// bool insertInto(String table_name, Vector<String> col_data, Vector<String> col_values){
	// 	return this->db.insertInto(table_name, col_data, col_values);
	// }



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
String getDBName() const {
	return db.get_db_name();
}

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

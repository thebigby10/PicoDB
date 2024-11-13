#include<iostream>

#include "../../src/Database.cpp"
#include "../../src/Table.cpp"
#include "../../src/Cell.cpp"

#include "../../src/FileHandler.cpp"
#include "../../src/Encryptor.cpp"

#include "../../src/Vector.cpp"
// #include "../../src/Date.cpp"

#include "../../src/String.cpp"
//#include "../../src/Map.cpp"

class PicoDB{
private:
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

	void select(String table_name, Vector<String> cols) {
		Table input_table;

		// Find the table by name
		for (int i = 0; i < db.get_tables().get_size(); i++) {
			if ((db.get_tables()[i].getTableName()) == (table_name)) {
				input_table = db.get_tables()[i];
				break;
			}
		}

		// If no columns specified, print the entire table
		if (cols.get_size() == 0) {
			db.printTable(input_table);
			return;
		}
		// Create a new table to store selected columns
		Table selected_table;
		selected_table.updateRecords(Vector<Vector<Cell>>());  // Initialize with empty data

		// Store indices of the specified columns in the headers
		Vector<int> selected_column_indices;
		Vector<String> selected_headers;

		for (int i = 0; i < cols.get_size(); i++) {
			for (int j = 0; j < input_table.getHeaders().get_size(); j++) {
				if (input_table.getHeaders()[j] == cols[i]) {
					selected_column_indices.push_back(j);
					selected_headers.push_back(cols[i]);
					break;
				}
			}
		}

		// Populate data for selected columns
		Vector<Vector<Cell>> filtered_data;
		for (int i = 0; i < input_table.getTableData().get_size(); i++) {
			Vector<Cell> row;
			for (int j = 0; j < selected_column_indices.get_size(); j++) {
				row.push_back(input_table.getTableData()[i][selected_column_indices[j]]);
			}
			filtered_data.push_back(row);
		}

		// Update selected_table with headers and filtered data
		selected_table.updateRecords(filtered_data);
    // Update selected_table with headers and filtered data
    selected_table.setHeaders(selected_headers);
    selected_table.updateRecords(filtered_data);

    // Print the selected table
    db.printTable(selected_table);
	}

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
};

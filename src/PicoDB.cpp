// #include "../include/PicoDB/PicoDB.h"

// bool PicoDB::createTable(String table_name, Vector<Vector<String>> col_data){
// 		this->db.get_tables().push_back(Table(table_name, col_data));
// 		return true;
// 	}

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

	// void PicoDB::update(String table_name, Vector<String>update_data, Vector<int >condition){
	// 	Database(table_name, update_data, condition);
	// }


	// bool insertInto(String table_name, Vector<String> col_data, Vector<String> col_values){
	// 	return this->db.insertInto(table_name, col_data, col_values);
	// }
// bool PicoDB::insertInto(String table_name, Vector<String> col_names, Vector<String> values) {
//    for (int i = 0; i < db.get_tables().get_size(); ++i) {
//        if (db.get_tables()[i].getTableName() == table_name) {
//            Table& table = db.get_tables()[i];
//            // Ensure the number of columns matches the number of values
//            if (col_names.get_size() == values.get_size()) {
//                Vector<Cell> row_data;
//                for (int j = 0; j < values.get_size(); ++j) {
//                    // Convert values to Cell objects based on data type
//                    // Assuming all values are strings for simplicity
//                    row_data.push_back(Cell(values[j]));
//                }
//                table.updateSingleRecord(row_data);
//            } else {
//                std::cerr << "Column count does not match value count" << std::endl;
//                return false;
//            }
//            return true;
//        }
//    }
//    std::cerr << "Table not found" << std::endl;
//    return false;
// }


	/*
	vector<vector< string > > selectData(string table_name, vector<string> cols){

	}

	vector<vector< string > > selectDataWhere(string table_name, vector<string> cols){

	}*/

	// bool PicoDB::saveDB(){
	// 	this->db.saveDB();
	// 	return true;
	// }
	/*
	bool dropTable(){

	}



	*/

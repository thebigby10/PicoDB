#include "../../include/PicoDB/PicoDB.h"
// #include "PicoDB.h"

// PicoDB::PicoDB(String db_name, String db_path, String username, String key, String table_delimiter) : db(db_name, db_path, username, key, table_delimiter) {}

// // PicoDB::PicoDB(String db_name, String db_path, String username, String key)
// // : db(db_name, db_path, username, key) {
// //         // No additional setup implemented in the constructor body yet
// // }

// bool PicoDB::createTable(String table_name, Vector<Vector<String>> col_data){
//     this->db.get_tables().push_back(Table(table_name, col_data));
//     return true;
// }

// // void select(String table_name, Vector<String> cols){
// // 	if(cols.get_size()==0){
// // 		Table input_table;
// // 		for(int i=0;i<db.get_tables().get_size();i++){
// // 			if((db.get_tables()[i].getTableName()) == (table_name)){
// // 				input_table = db.get_tables()[i];
// // 				break;
// // 			}
// // 		}
// // 		db.printTable(input_table);
// // 	}
// // }

// // void update(String table_name, Vector<String>update_data, Vector<int >condition){
// //     //Database(table_name, update_data, condition);
// // }

// void PicoDB::select(String table_name, Vector<String> cols) {
//     Table input_table;

//     // Find the table by name
//     for (int i = 0; i < db.get_tables().get_size(); i++) {
//         if ((db.get_tables()[i].getTableName()) == (table_name)) {
//             input_table = db.get_tables()[i];
//             break;
//         }
//     }

//     // If no columns specified, print the entire table
//     if (cols.get_size() == 0) {
//         db.printTable(input_table);
//         return;
//     }
//     // Create a new table to store selected columns
//     Table selected_table;
//     selected_table.updateRecords(Vector<Vector<Cell>>());  // Initialize with empty data

//     // Store indices of the specified columns in the headers
//     Vector<int> selected_column_indices;
//     Vector<String> selected_headers;

//     for (int i = 0; i < cols.get_size(); i++) {
//         for (int j = 0; j < input_table.getHeaders().get_size(); j++) {
//             if (input_table.getHeaders()[j] == cols[i]) {
//                 selected_column_indices.push_back(j);
//                 selected_headers.push_back(cols[i]);
//                 break;
//             }
//         }
//     }

//     // Populate data for selected columns
//     Vector<Vector<Cell>> filtered_data;
//     for (int i = 0; i < input_table.getTableData().get_size(); i++) {
//         Vector<Cell> row;
//         for (int j = 0; j < selected_column_indices.get_size(); j++) {
//             row.push_back(input_table.getTableData()[i][selected_column_indices[j]]);
//         }
//         filtered_data.push_back(row);
//     }

//     // Update selected_table with headers and filtered data
//     selected_table.updateRecords(filtered_data);
// // Update selected_table with headers and filtered data
// selected_table.setHeaders(selected_headers);
// selected_table.updateRecords(filtered_data);

// // Print the selected table
// db.printTable(selected_table);
// }

// bool PicoDB::insertInto(String table_name, Vector<String> col_names, Vector<String> values) {
//     return this->db.insertInto(table_name, col_names, values);
// }


// /*
// vector<vector< string > > selectData(string table_name, vector<string> cols){

// }

// vector<vector< string > > selectDataWhere(string table_name, vector<string> cols){

// }*/

// void PicoDB::addUser (const String& username, const String& tableName) {
//     UserPermissionManager permissionManager(db);
//     permissionManager.addUser(username, tableName);
// }

// void PicoDB::grantPermission(const String& username, const String& tableName) {
//     UserPermissionManager permissionManager(this->db);
//     permissionManager.grantPermission(username, tableName);
// }

// void PicoDB::revokePermission(const String& username, const String& tableName) {
//     UserPermissionManager permissionManager(this->db);
//     permissionManager.revokePermission(username, tableName);
// }

// bool PicoDB::saveDB(){
//     this->db.saveDB();
//     return true;
// }
// /*
// bool dropTable(){

// }
// */
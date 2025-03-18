#include "../../include/PicoDB/Table.h"

// // Default constructor
// Table::Table() : table_name(""), headers(), data_types(), constraints(), table_data() {}

// // new constructor - is used in createTable in picoDB class
// Table::Table(String table_name, Vector<Vector<String>> col_data) {
// 	this->table_name = table_name;
// 	extract_col_data(col_data);
// }

// // constructor overloader - is used in loadCurrentTables in Database class
// Table::Table(String table_name, Vector<String> headers, Vector<String> data_types, Vector<String> constraints)
// 	: table_name(table_name), headers(headers), data_types(data_types), constraints(constraints) {
// }

// // update table with new data
// void Table::extract_col_data(Vector<Vector<String>> temp_col_data) {
// 	int num_headers = temp_col_data.get_size();
// 	for (int i = 0; i < num_headers; ++i) {
// 		if (temp_col_data[i].get_size() > 0) {
// 			headers.push_back(temp_col_data[i][0]);
// 		}
// 		if (temp_col_data[i].get_size() > 1) {
// 			data_types.push_back(temp_col_data[i][1]);
// 		}
// 		if (temp_col_data[i].get_size() > 2) {
// 			constraints.push_back(temp_col_data[i][2]);
// 		}
// 	}
// }

// // to update table cells
// void Table::updateRecords(Vector<Vector<Cell>> cell_data) {
// 	this->table_data = cell_data;
// }

// void Table::updateSingleRecord(Vector<Cell> cell_data) {
// 	this->table_data.push_back(cell_data);
// }

// // Getter for table_name
// String Table::getTableName() const {
// 	return table_name;
// }

// // Getter for headers
// Vector<String> Table::getHeaders() const {
// 	return headers;
// }

// // Getter for data_types
// Vector<String> Table::getDataTypes() const {
// 	return data_types;
// }

// // Getter for constraints
// Vector<String> Table::getConstraints() const {
// 	return constraints;
// }

// // Getter for table_data
// Vector<Vector<Cell>> Table::getTableData() const {
// 	return table_data;
// }

// // Set headers
// void Table::setHeaders(Vector<String> headers) {
// 	this->headers = headers;
// }

// // Additional methods for row management
// Vector<String> Table::get_Row() {
// 	return headers;
// }

// int Table::get_RowSize() {
// 	return table_data.get_size();
// }

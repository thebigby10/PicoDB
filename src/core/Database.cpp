// // Database.cpp
#include "../../include/PicoDB/Database.h"


// #include "Database.h"
// #include "Table.h"
// #include "Cell.h"
// #include <iostream>

// bool Database::insertInto(String table_name, Vector<String> cols, Vector<String> cell_data) {
//     int tables_num = tables.get_size();

//     for (int i = 0; i < tables_num; i++) {
//         if (table_name == tables[i].getTableName()) {
//             Vector<String> data_types = tables[i].getDataTypes();
//             Vector<String> headers = tables[i].getHeaders();
//             int num_of_columns = headers.get_size();

//             // Check if cols and cell_data match the table's headers
//             if (cols.get_size() != cell_data.get_size() || cols.get_size() > num_of_columns) {
//                 std::cout << "Error: Column and data size mismatch." << std::endl;
//                 return false;
//             }

//             Vector<Cell> single_line_cell_data;

//             for (int j = 0; j < num_of_columns; j++) {
//                 bool column_matched = false;

//                 // Check if headers[j] exists in cols
//                 for (int k = 0; k < cols.get_size(); k++) {
//                     if (headers[j] == cols[k]) {
//                         column_matched = true;

//                         // Add cell data according to the data type
//                         if (data_types[j] == String("INT")) {
//                             single_line_cell_data.push_back(Cell(cell_data[k].toInt()));
//                         } else if (data_types[j] == String("DOUBLE")) {
//                             single_line_cell_data.push_back(Cell(cell_data[k].toDouble()));
//                         } else if (data_types[j] == String("BOOLEAN")) {
//                             single_line_cell_data.push_back(Cell(cell_data[k].toBool()));
//                         } else {
//                             single_line_cell_data.push_back(Cell(cell_data[k]));
//                         }
//                         break;
//                     }
//                 }

//                 // If column not found in cols, add a default value or handle as needed
//                 if (!column_matched) {
//                     std::cout << "Warning: Column " << headers[j] << " not found in input cols. Adding default value." << std::endl;
//                     single_line_cell_data.push_back(Cell());  // Assuming default constructor in Cell
//                 }
//             }

//             // Validate Primary Key constraint
//             if (!tables[i].validatePrimaryKey(single_line_cell_data)) {
//                 std::cout << "Error: Primary Key violation" << std::endl;
//                 return false;
//             }

//             // Validate Foreign Key constraint
//             if (!tables[i].validateForeignKey(single_line_cell_data)) {
//                 std::cout << "Error: Foreign Key violation" << std::endl;
//                 return false;
//             }

//             // Update the table with the new row data
//             tables[i].updateSingleRecord(single_line_cell_data);
//             return true;  // Insertion successful
//         }
//     }

//     // Table not found
//     std::cout << "Error: Table " << table_name << " not found." << std::endl;
//     return false;
// }

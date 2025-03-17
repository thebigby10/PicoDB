#ifndef DATABASE_H // Include guard start
#define DATABASE_H

#include <iostream>
#include <filesystem>
#include "String.h"
#include "Vector.h"
#include "Encryptor.h"
#include "Table.h"
#include "FileHandler.h"
#include "Cell.h"
#include "ConfigManager.h"
#include "StringVectorConverter.h"

#define DEBUG false


class Database{
private:
	String db_name;
	String db_path;
	String username;
	String key;
	String delimiter;
	bool encryption = true;
	String admin;
	Vector<Table> tables;
	Vector<Vector<String>> allUserPermissionsInfo; //needed for checking existing user permissions while adding users or granting permissions
	Vector<String> currentUserPermissions;
	// Vector<>permissions;
public:

	// Database(string db_name, bool force_create, bool encryption, string file_path )
	Database(String db_name, String db_path, String username, String key, String table_delimiter = String(";_;pico;_;")){
		this->db_name = db_name;
		this->db_path = db_path;
		this->username = username;
		this->key = key;
		this->delimiter = table_delimiter;
		this->admin = username;

		//check if file exists
		FileHandler conf_file = FileHandler(db_path+String("/")+db_name+String(".config")); //path to config file
		if(conf_file.fileExists()){

			// Conf manager fetches raw data ✅
			ConfigManager conf_manager(db_path+String("/")+db_name+String(".config"));

			// convert the config file into variables ✅
			this->delimiter = conf_manager.get_t_delimiter();
			this->admin = conf_manager.get_admin();
			this->allUserPermissionsInfo = conf_manager.get_permissions();

			// check if the user exists ✅
			bool user_exists = false;

			if (!isAdmin()) {
				int permissions_size = allUserPermissionsInfo.get_size();
				for (int i=0; i<permissions_size; i+=2) {
					if (username == allUserPermissionsInfo[i][0]) {
						// we're taking [i][0] and i+=2 cause every 2nd vector in allUserPermissionInfo contains the table name, need to use constants here later
						Vector<String> temp = allUserPermissionsInfo[i+1];
						this->currentUserPermissions = temp;
						user_exists = true;
						break;
					}
				}
			}


			if (user_exists || isAdmin()) {
				//convert the tables into vector ✅
				loadCurrentTables(conf_manager);
			} else {
				// throw exception
			}

		}
		else{
			//create config file
			ConfigManager conf_manager(db_path+String("/")+db_name+".config");
			conf_manager.createConfig(db_name,table_delimiter,username, true);
		}
	}

	bool createTable(String table_name, Vector<Vector<String>> col_data){
		// check if user already has accecss to table
		if (!isAdmin()) {
			int current_permission_size = currentUserPermissions.get_size();
			bool table_in_current_permissions = false;
			for (int i=0; i<current_permission_size; i++) {
				if (currentUserPermissions[i] == table_name) {
					table_in_current_permissions = true;
					std::cout << "Table already exists. Try with a different name." << std::endl;
					break;
				}
			}

			if (!table_in_current_permissions) {
				// update the currentUserPermissions
				currentUserPermissions.push_back(table_name);
				// update the allUserPermissionsInfo
				int all_user_permissions_size = allUserPermissionsInfo.get_size();
				for (int i=0; i<all_user_permissions_size; i+=2) {
					if (allUserPermissionsInfo[i][0] == username) {
						allUserPermissionsInfo[i+1].push_back(table_name);
						break;
					}
				}
			}
		}

		tables.push_back(Table(table_name, col_data));
		return true;
	}

    // bool update(String table_name, Vector<String> update_values, String condition){
	// 	if(DEBUG) cout << "[DEBUG] Searching for table: " << table_name << std::endl;
	// 	Table input_table;
	// 	bool table_found = false;

	// 	// Find the table by name

	// 	for (int i = 0; i < tables.get_size(); i++) {
	// 		if(DEBUG) cout << "[DEBUG] Checking table: " << tables[i].getTableName() << std::endl;
	// 		if (tables[i].getTableName() == table_name) {
	// 			input_table = tables[i];
	// 			table_found = true;
	// 			if(DEBUG) cout << "[DEBUG] Table found!" << std::endl;
	// 			break;
	// 		}
	// 	}
	// 	if(DEBUG) cout<<endl;

	// 	if (!table_found) {
	// 		std::cerr << "Table not found: " << table_name << std::endl;
	// 		return false;
	// 	}

	// if(DEBUG){ std::cout << "[DEBUG] Selected columns: ";
	// for (int i = 0; i < update_values.get_size(); i++) {
	// 	std::cout << update_values[i] << " ";
	// }
	// std::cout << std::endl<<std::endl;}

	// 	// Store selected column indices
	// 	Vector<int> selected_column_indices;
	// 	for (int i = 0; i < update_values.get_size(); i++) {
	// 		for (int j = 0; j < input_table.getHeaders().get_size(); j++) {
	// 			if (input_table.getHeaders()[j] == update_values[i]) {
	// 				selected_column_indices.push_back(j);
	// 			if(DEBUG) cout << "[DEBUG] Column " << update_values[i] << " found at index " << j << std::endl;
	// 				break;
	// 			}
	// 		}
	// 	}
	// 	if(DEBUG) cout<<endl;

	// 	// Parse complex conditions
	// 	Vector<int> condition_indices;
	// 	Vector<String> condition_ops;
	// 	Vector<String> condition_values;
	// 	Vector<String> logical_ops;


	// // tokenize the conditions
	// 	if (condition != String("")) {
	// 		Vector<String> tokens;
	// 		String current_token;
	// 		String op;
	// 		bool in_string = false;

	// 		for (size_t i = 0; i < condition.length(); i++) {
	// 			char c = condition[i];
	// 			if (c == ' ' && !in_string) {
	// 				if (!current_token.trim().empty()) {
	// 					tokens.push_back(current_token.trim());
	// 					current_token.clear();
	// 				}
	// 			} else if (c == '"') {
	// 				in_string = !in_string;
	// 			} else {
	// 				current_token = current_token + c;
	// 			}
	// 		}
	// 		if (!current_token.empty()) {
	// 			tokens.push_back(current_token.trim());
	// 		}

	// 		bool expecting_value = false;  // Track when an operator is found

	// 		for (size_t i = 0; i < tokens.get_size(); i++) {
	// 			if (tokens[i] == String("AND") || tokens[i] == String("OR")) {
	// 				logical_ops.push_back(tokens[i]);
	// 				expecting_value = false;  // Reset flag after logical operator
	// 			} else if (tokens[i] == String("=") || tokens[i] == String("!=") || tokens[i] == String(">") ||
	// 					tokens[i] == String("<") || tokens[i] == String(">=") || tokens[i] == String("<=") ||
	// 					tokens[i] == String("LIKE")) {
	// 				condition_ops.push_back(tokens[i]);
	// 				expecting_value = true;  // Next token should be a value
	// 			} else if (expecting_value) {
	// 				condition_values.push_back(tokens[i]);
	// 				expecting_value = false;  // Reset flag after capturing a value
	// 			} else {
	// 				for (int j = 0; j < input_table.getHeaders().get_size(); j++) {
	// 					if (input_table.getHeaders()[j] == tokens[i]) {
	// 						condition_indices.push_back(j);
	// 						break;
	// 					}
	// 				}
	// 			}
	// 		}
	// 		if(DEBUG){std::cout << "[DEBUG] Condition: " << condition << std::endl;
	// 			std::cout << "[DEBUG] Parsed tokens: ";
	// 			for (int i = 0; i < tokens.get_size(); i++) {
	// 				std::cout << tokens[i] << " ";
	// 			}
	// 			std::cout << std::endl;

	// 			std::cout << "[DEBUG] Condition Indices: ";
	// 			for (int i = 0; i < condition_indices.get_size(); i++) {
	// 				std::cout << condition_indices[i] << " ";
	// 			}
	// 			std::cout << std::endl;

	// 			std::cout << "[DEBUG] Condition Operators: ";
	// 			for (int i = 0; i < condition_ops.get_size(); i++) {
	// 				std::cout << condition_ops[i] << " ";
	// 			}
	// 			std::cout << std::endl;

	// 			std::cout << "[DEBUG] Condition Values: ";
	// 			for (int i = 0; i < condition_values.get_size(); i++) {
	// 				std::cout << condition_values[i] << " ";
	// 			}
	// 			std::cout << std::endl;
	// 		}

	// 	}

	// 	// Apply condition filtering
	// 	Vector<Vector<Cell>> filtered_data;
	// 	for (int i = 0; i < input_table.getTableData().get_size(); i++) {
	// 		if (evaluateComplexCondition(input_table.getTableData()[i], condition_indices, condition_ops, condition_values, logical_ops)) {
	// 			filtered_data.push_back(input_table.getTableData()[i]);
	// 		}
	// 	}

	// 	// Create new table with selected columns
	// 	Table selected_table;
	// 	Vector<String> selected_headers;
	// 	for (int i = 0; i < selected_column_indices.get_size(); i++) {
	// 		selected_headers.push_back(input_table.getHeaders()[selected_column_indices[i]]);
	// 	}
	// 	selected_table.setHeaders(selected_headers);

	// 	Vector<Vector<Cell>> selected_data;
	// 	for (int i = 0; i < filtered_data.get_size(); i++) {
	// 		Vector<Cell> row;
	// 		for (int j = 0; j < selected_column_indices.get_size(); j++) {
	// 			row.push_back(filtered_data[i][selected_column_indices[j]]);
	// 		}
	// 		selected_data.push_back(row);
	// 	}
	// 	selected_table.updateRecords(selected_data);

	// //debugging
	// 	// std::cout << "\tFiltering table: " << table_name << std::endl;
	// 	// std::cout << "\tCondition: " << condition << std::endl;
	// 	// std::cout << "\tNumber of rows before filtering: " << input_table.getTableData().get_size() << std::endl;

	// 	return true;
	// }

	// Load tables from the configuration file
	void loadCurrentTables(ConfigManager conf_manager){
		ConfigManager conf_file = conf_manager;
		StringVectorConverter converter;
		Encryptor encryptor(String(key).toInt());

		// fetch the config file data and add it to table_name, headers, types and constraints
		Vector<Vector<String>> temp_data = conf_file.get_table_meta_data();
		int temp_data_size = temp_data.get_size();

		if (!isAdmin()) {
			for(int i=0; i<temp_data_size; i+=4) {
				int current_permission_size = currentUserPermissions.get_size();
				for (int j=0; j<current_permission_size; j++) {
					if (temp_data[i][0] == currentUserPermissions[j]){
						this->tables.push_back(Table(temp_data[i][0],temp_data[i+1],temp_data[i+2],temp_data[i+3]));
					}
				}
			}
		} else {
			for(int i=0; i<temp_data_size; i+=4) {
				this->tables.push_back(Table(temp_data[i][0],temp_data[i+1],temp_data[i+2],temp_data[i+3]));
			}
		}

		// decrypt the csv file data related to the table and copy the info
		int table_size = tables.get_size();
		for(int i=0; i<table_size; i++) {
			String table_name = tables[i].getTableName();
			Vector<String> data_types = tables[i].getDataTypes();
			Vector<Vector<Cell>> cell_data;
			Vector<Vector<String>> table_data_from_file;
			String table_string_data;

			// open the specific table file and decrypt it
			FileHandler table_file = FileHandler(db_path+String("/")+table_name+String(".csv")); //path to that table's csv file
			table_string_data = table_file.readFromFile();
			table_string_data = encryptor.decryptData(table_string_data); // decrypt fetched string data

			//converter.stringToVector(table_string_data, delimiter);
			table_data_from_file = converter.stringToVector(table_string_data, delimiter);


			// load the data to table cells
			int num_of_types = data_types.get_size();
			int num_of_rows = table_data_from_file.get_size();

			for (int j=0; j<num_of_rows; j++) {
				Vector<Cell> single_line_cell_data;
				for (int k=0; k<num_of_types; k++) {
					if (data_types[k] == String("INT")) {
						// Conversion to int
						single_line_cell_data.push_back(Cell(table_data_from_file[j][k].toInt()));
					} else if (data_types[k] == String("DOUBLE")) {
						// Conversion to double
						single_line_cell_data.push_back(Cell(table_data_from_file[j][k].toDouble()));
					} else if (data_types[k] == String("BOOLEAN")) {
						// Conversion to boolean
						single_line_cell_data.push_back(Cell(table_data_from_file[j][k].toBool()));
					} else {
						// Default case (e.g., assume it's a string)
						single_line_cell_data.push_back(Cell(table_data_from_file[j][k]));
					}
				}
				cell_data.push_back(single_line_cell_data);
			}
			tables[i].updateRecords(cell_data);
		}
	}

	// Check if the current user is an admin
	bool isAdmin() {
		return this->username == this->admin; // Compares the current user with the stored admin username
	}

	// Save all table data to files
	void saveTableData(){
		int table_size = tables.get_size();
		for (int i=0; i<table_size; i++) {
			String table_name = tables[i].getTableName();
			int num_columns = tables[i].getHeaders().get_size();

			Vector<Vector<Cell>> cells = tables[i].getTableData();
			Vector<Vector<String>> table_data;

			int num_rows = cells.get_size();
			for (int j=0; j<num_rows; j++) {
				Vector<String> row_data;
				for (int k=0; k<num_columns; k++) {
					DataType dataType = cells[j][k].getDataType();

					if (dataType == DataType::INTEGER) {
						// conversion from int to string
						row_data.push_back(String::toString(cells[j][k].getInt()));
					} else if (dataType == DataType::DOUBLE) {
						// conversion from double to string
						row_data.push_back(String::toString(cells[j][k].getDouble()));
					} else if (dataType == DataType::BOOLEAN) {
						// conversion from boolean to string
						row_data.push_back(String::toString(cells[j][k].getBoolean()));
					} else {
						// code to execute if none of the cases match
						row_data.push_back(cells[j][k].getString());
					}
				}
				table_data.push_back(row_data);
			}

			StringVectorConverter converter;
			Encryptor encryptor(String(key).toInt());

			String file_data = converter.vector2DToString(table_data, delimiter);  // converts vector data to string for writing
			file_data = encryptor.encryptData(file_data);   // encrypts the data

			FileHandler table_file(db_path+String("/")+table_name+String(".csv")); //path to that table's csv file

			table_file.createFile();
			table_file.writeToFile(file_data);
		}
	}

	// Save database metadata to the config file
	void saveDBMetaData() {
		StringVectorConverter converter;
		String conf_data;
		conf_data+=String("[Database]\n");
		conf_data+=String("database_name = ") + db_name + String("\n"); //Check
		conf_data+=String("file_path = ") + db_path+String("/")+ db_name + ".config" + String("\n");
		conf_data+=String("table_delimiter = ") + delimiter + String("\n");
		conf_data+=String("\n");
		conf_data+=String("[Admin]\n");
		conf_data+=String("username = ") + admin + String("\n");
		conf_data+=String("\n");
		conf_data+=String("[Permission]\n");
		conf_data+= converter.vector2DToString(allUserPermissionsInfo, ",");
		conf_data+=String("\n");
		conf_data+=String("[Encryption]\n");
		if(encryption) conf_data+=String("enabled = true\n");
		else conf_data+=String("enabled = false\n");
		conf_data+=String("\n");
		conf_data+=String("[Tables]\n");


		String table_metadata = TableMetaData();
		conf_data += table_metadata;

		ConfigManager conf_manager(db_path+String("/")+db_name+String(".config"));
		conf_manager.updateConfig(conf_data);

		// FileHandler config_file(db_path+String("/")+db_name+String(".config"));

		// config_file.createFile();
		// config_file.writeToFile(conf_data);
	}

	// Generate table metadata
	String TableMetaData(){
		String table_meta_data;
		StringVectorConverter converter;
		ConfigManager conf_manager(db_path+String("/")+db_name+String(".config"));

		if (isAdmin()) {
			int tables_num = tables.get_size();
			for(int i=0; i<tables_num; i++) {
				//for table names
				table_meta_data += tables[i].getTableName();
				table_meta_data += String("\n");

				//for headers
				table_meta_data += converter.vectorToString(tables[i].getHeaders());

				//for data_types
				table_meta_data += converter.vectorToString(tables[i].getDataTypes());

				//for constraints
				table_meta_data += converter.vectorToString(tables[i].getConstraints());
			}
		} else {
			Vector<Vector<String>> temp_table_meta_data = conf_manager.get_table_meta_data();

			int temp_table_meta_data_size = temp_table_meta_data.get_size();
			int tables_num = tables.get_size();
			for (int i=0; i<tables_num; i++) {
				bool table_exists_in_config = false;
				for (int j=0; j<temp_table_meta_data_size; j+=4) {
					if (tables[i].getTableName() == temp_table_meta_data[j][0]) {
						temp_table_meta_data[j+1] = tables[i].getHeaders();
						temp_table_meta_data[j+2] = tables[i].getDataTypes();
						temp_table_meta_data[j+3] = tables[i].getConstraints();
						table_exists_in_config = true;
						break;
					}
				}

				if (!table_exists_in_config) {
					// for tables that non admin users will create
					Vector<String> new_table_name;
					new_table_name.push_back(tables[i].getTableName());

					temp_table_meta_data.push_back(new_table_name);
					temp_table_meta_data.push_back(tables[i].getHeaders());
					temp_table_meta_data.push_back(tables[i].getDataTypes());
					temp_table_meta_data.push_back(tables[i].getConstraints());
				}
			}

			table_meta_data += converter.vector2DToString(temp_table_meta_data, delimiter);
		}
		return table_meta_data;
	}

	// Save the database (both metadata and table data)
	bool saveDB(){
		saveDBMetaData();
		saveTableData();
		return true;
	}

	// Insert data into a specific table
	bool insertInto(String table_name, Vector<String> cols, Vector<String> cell_data) {
    // Find the corresponding table
    Table* table = nullptr;
    for (int i = 0; i < tables.get_size(); ++i) {
        if (tables[i].getTableName() == table_name) {
            table = &tables[i];
            break;
        }
    }

    if (!table) {
        std::cerr << "Table not found: " << table_name << std::endl;
        return false;
    }

    // Prepare the row of cells
    Vector<Cell> row;
    for (int i = 0; i < cols.get_size(); ++i) {
        row.push_back(Cell(cell_data[i]));  // Assuming all values are strings (can be enhanced based on types)
    }

    // 1. Check Primary Key Constraints (ensure no duplicate primary key)
    Vector<int> primary_key_indices = table->getPrimaryKeyIndices();

    for (int i = 0; i < primary_key_indices.get_size(); ++i) {
        int pk_index = primary_key_indices[i];
        if (pk_index >= cols.get_size()) {
            std::cerr << "Error: Primary key index out of bounds!" << std::endl;
            return false;  // Index out of bounds
        }

        for (int j = 0; j < table->getTableData().get_size(); ++j) {
            if (table->getTableData()[j][pk_index].getData() == row[pk_index].getData()) {
                std::cerr << "Error: Duplicate primary key value for column " << cols[pk_index] << std::endl;
                return false;  // Duplicate primary key found, abort insertion
            }
        }
    }

    // 2. Check Foreign Key Constraints
    Vector<pair<int, String>> foreign_key_indices = table->getForeignKeyIndices();
    for (int i = 0; i < cols.get_size(); ++i) {
        for (int j = 0; j < foreign_key_indices.get_size(); ++j) {
            auto& fk = foreign_key_indices[j];  // Access the foreign key pair
            if (fk.first == i) { // If the column is a foreign key
                if (!foreignKeyExists(table, i, cell_data[i])) {
                    std::cerr << "Error: Foreign key constraint failed for column " << cols[i] << " with value " << cell_data[i] << std::endl;
                    return false;  // Foreign key value not found in the referenced table
                }
            }
        }
    }

    // 3. If no constraint violations, insert the data into the table
    table->updateSingleRecord(row);
    return true;
}

	//function for printing a table
	void printTable(Table& table) {
		// Print table name
		std::cout << "Table: " << table.getTableName() << std::endl;

		// Get the column headers
		Vector<String> headers = table.getHeaders();

		// Determine the maximum width for each column
		Vector<size_t> colWidths;
		for (int i = 0; i < headers.get_size(); ++i) {
			colWidths.push_back(0); // Initialize each element to 0
		}

		// First, calculate the maximum length of each column (header + data)
		for (int i = 0; i < headers.get_size(); ++i) {
			colWidths[i] = headers[i].length();  // Start by considering the header size
		}

		// Also check the row data for each column to find the longest string in that column
		Vector<Vector<Cell>> rows = table.getTableData();
		for (int i = 0; i < rows.get_size(); ++i) {
			for (int j = 0; j < rows[i].get_size(); ++j) {
				//size_t cellLength = rows[i][j].getString().length();
				size_t cellLength ;
				String c_data;
				DataType dataType = rows[i][j].getDataType();

				if (dataType == DataType::INTEGER) {
					// conversion from int to string
					c_data = String::toString(rows[i][j].getInt());
				} else if (dataType == DataType::DOUBLE) {
					// conversion from double to string
					c_data = String::toString(rows[i][j].getDouble());
				} else if (dataType == DataType::BOOLEAN) {
					// conversion from boolean to string
					c_data = String::toString(rows[i][j].getBoolean());
				} else {
					// code to execute if none of the cases match
					c_data = rows[i][j].getString();
				}

				cellLength = c_data.length();
				if (cellLength > colWidths[j]) {
					colWidths[j] = cellLength;  // Update column width if the cell's length is greater
				}
			}
		}
		// --- Added roof line here ---
		for (int i = 0; i < headers.get_size(); ++i) {
			std::cout << "+";
			for (size_t j = 0; j < colWidths[i] + 2; ++j) {
				std::cout << "-";  // Create a separator line with appropriate width
			}
		}
		std::cout << "+" << std::endl;  // End line for the roof
		// --- End of roof line ---

		// Print column headers with dynamic widths
		for (int i = 0; i < headers.get_size(); ++i) {
			std::cout << "| " << headers[i];
			// Pad the header to match the max width
			for (size_t j = headers[i].length(); j < colWidths[i]; ++j) {
				std::cout << " ";
			}
			std::cout << " ";  // Space after each column
		}
		std::cout << "|" << std::endl;

		// Print a line under the headers to form a box
		for (int i = 0; i < headers.get_size(); ++i) {
			std::cout << "+";
			for (size_t j = 0; j < colWidths[i] + 2; ++j) {
				std::cout << "-";  // Create a separator line with appropriate width
			}
		}
		std::cout << "+" << std::endl;

		// Print rows with dynamic column widths
		if (rows.get_size() == 0) {
			std::cout << "No records found." << std::endl;
		} else {
			for (int i = 0; i < rows.get_size(); ++i) {
				for (int j = 0; j < rows[i].get_size(); ++j) {
					String cell_data;
					DataType dataType = rows[i][j].getDataType();

					if (dataType == DataType::INTEGER) {
						// conversion from int to string
						cell_data = String::toString(rows[i][j].getInt());
					} else if (dataType == DataType::DOUBLE) {
						// conversion from double to string
						cell_data = String::toString(rows[i][j].getDouble());
					} else if (dataType == DataType::BOOLEAN) {
						// conversion from boolean to string
						cell_data = String::toString(rows[i][j].getBoolean());
					} else {
						// code to execute if none of the cases match
						cell_data = rows[i][j].getString();
					}

					std::cout << "| " << cell_data;
					// Pad each column to the dynamic width
					for (size_t k = cell_data.length(); k < colWidths[j]; ++k) {
						std::cout << " ";
					}
					std::cout << " ";  // Space after each column
				}
				std::cout << "|" << std::endl;
			}
		}

		// Print bottom line to close the box
		for (int i = 0; i < headers.get_size(); ++i) {
			std::cout << "+";
			for (size_t j = 0; j < colWidths[i] + 2; ++j) {
				std::cout << "-";  // Closing line for each column
			}
		}
		std::cout << "+" << std::endl;  // End line for the bottom of the table
	}

//new select
// Table select(Table input_table, Vector<String> cols, String condition){
//     Table selected_table;

//        // If no columns are specified, select all columns
//        if (cols.get_size() == 0) {
//            cols = input_table.getHeaders();  // Set to all columns if empty
//        }

//        // Store indices of the specified columns in the headers
//        Vector<int> selected_column_indices;
//        Vector<String> selected_headers;

//        for (int i = 0; i < cols.get_size(); i++) {
//            for (int j = 0; j < input_table.getHeaders().get_size(); j++) {
//                if (input_table.getHeaders()[j] == cols[i]) {
//                    selected_column_indices.push_back(j);
//                    selected_headers.push_back(cols[i]);
//                    break;
//                }
//            }
//        }

//        // Apply condition filtering
//        Vector<Vector<Cell>> filtered_data;
//        for (int i = 0; i < input_table.getTableData().get_size(); i++) {
//            // Check if the row meets the condition (if condition is non-empty)
//            if (condition.empty() || evaluateComplexCondition(input_table.getTableData()[i], selected_column_indices, condition)) {
//                Vector<Cell> row;
//                for (int j = 0; j < selected_column_indices.get_size(); j++) {
//                    row.push_back(input_table.getTableData()[i][selected_column_indices[j]]);
//                }
//                filtered_data.push_back(row);
//            }
//        }

//        // Update the selected table with headers and filtered data
//        selected_table.setHeaders(selected_headers);
//        selected_table.updateRecords(filtered_data);

//        // Return the selected table
//        return selected_table;
// }



//previous select
Table select(Table table, Vector<String> cols, String condition) {
	// if(DEBUG) cout << "[DEBUG] Searching for table: " << table_name << std::endl;
		Table input_table = table;
		// bool table_found = false;

		// Find the table by name

		// for (int i = 0; i < tables.get_size(); i++) {
		// 	if(DEBUG) cout << "[DEBUG] Checking table: " << tables[i].getTableName() << std::endl;
		// 	if (tables[i].getTableName() == table_name) {
		// 		input_table = tables[i];
		// 		table_found = true;
		// 		if(DEBUG) cout << "[DEBUG] Table found!" << std::endl;
		// 		break;
		// 	}
		// }
		// if(DEBUG) cout<<endl;

		// if (!table_found) {
		// 	std::cerr << "Table not found: " << table_name << std::endl;
		// 	return Table();
		// }

	if(DEBUG){ std::cout << "[DEBUG] Selected columns: ";
	for (int i = 0; i < cols.get_size(); i++) {
		std::cout << cols[i] << " ";
	}
	std::cout << std::endl<<std::endl;}

		// Store selected column indices
		Vector<int> selected_column_indices;
		for (int i = 0; i < cols.get_size(); i++) {
			for (int j = 0; j < input_table.getHeaders().get_size(); j++) {
				if (input_table.getHeaders()[j] == cols[i]) {
					selected_column_indices.push_back(j);
				if(DEBUG) cout << "[DEBUG] Column " << cols[i] << " found at index " << j << std::endl;
					break;
				}
			}
		}
		if(DEBUG) cout<<endl;

		// Parse complex conditions
		Vector<int> condition_indices;
		Vector<String> condition_ops;
		Vector<String> condition_values;
		Vector<String> logical_ops;


	// tokenize the conditions
		if (condition != String("")) {
			Vector<String> tokens;
			String current_token;
			String op;
			bool in_string = false;

			for (size_t i = 0; i < condition.length(); i++) {
				char c = condition[i];
				if (c == ' ' && !in_string) {
					if (!current_token.trim().empty()) {
						tokens.push_back(current_token.trim());
						current_token.clear();
					}
				} else if (c == '"') {
					in_string = !in_string;
				} else {
					current_token = current_token + c;
				}
			}
			if (!current_token.empty()) {
				tokens.push_back(current_token.trim());
			}

			bool expecting_value = false;  // Track when an operator is found

			for (size_t i = 0; i < tokens.get_size(); i++) {
				if (tokens[i] == String("AND") || tokens[i] == String("OR")) {
					logical_ops.push_back(tokens[i]);
					expecting_value = false;  // Reset flag after logical operator
				} else if (tokens[i] == String("=") || tokens[i] == String("!=") || tokens[i] == String(">") ||
						tokens[i] == String("<") || tokens[i] == String(">=") || tokens[i] == String("<=") ||
						tokens[i] == String("LIKE")) {
					condition_ops.push_back(tokens[i]);
					expecting_value = true;  // Next token should be a value
				} else if (expecting_value) {
					condition_values.push_back(tokens[i]);
					expecting_value = false;  // Reset flag after capturing a value
				} else {
					for (int j = 0; j < input_table.getHeaders().get_size(); j++) {
						if (input_table.getHeaders()[j] == tokens[i]) {
							condition_indices.push_back(j);
							break;
						}
					}
				}
			}
			if(DEBUG){std::cout << "[DEBUG] Condition: " << condition << std::endl;
				std::cout << "[DEBUG] Parsed tokens: ";
				for (int i = 0; i < tokens.get_size(); i++) {
					std::cout << tokens[i] << " ";
				}
				std::cout << std::endl;

				std::cout << "[DEBUG] Condition Indices: ";
				for (int i = 0; i < condition_indices.get_size(); i++) {
					std::cout << condition_indices[i] << " ";
				}
				std::cout << std::endl;

				std::cout << "[DEBUG] Condition Operators: ";
				for (int i = 0; i < condition_ops.get_size(); i++) {
					std::cout << condition_ops[i] << " ";
				}
				std::cout << std::endl;

				std::cout << "[DEBUG] Condition Values: ";
				for (int i = 0; i < condition_values.get_size(); i++) {
					std::cout << condition_values[i] << " ";
				}
				std::cout << std::endl;
			}

		}

		// Apply condition filtering
		Vector<Vector<Cell>> filtered_data;
		for (int i = 0; i < input_table.getTableData().get_size(); i++) {
			if (evaluateComplexCondition(input_table.getTableData()[i], condition_indices, condition_ops, condition_values, logical_ops)) {
				filtered_data.push_back(input_table.getTableData()[i]);
			}
		}

		// Create new table with selected columns
		Table selected_table;
		Vector<String> selected_headers;
		for (int i = 0; i < selected_column_indices.get_size(); i++) {
			selected_headers.push_back(input_table.getHeaders()[selected_column_indices[i]]);
		}
		selected_table.setHeaders(selected_headers);

		Vector<Vector<Cell>> selected_data;
		for (int i = 0; i < filtered_data.get_size(); i++) {
			Vector<Cell> row;
			for (int j = 0; j < selected_column_indices.get_size(); j++) {
				row.push_back(filtered_data[i][selected_column_indices[j]]);
			}
			selected_data.push_back(row);
		}
		selected_table.updateRecords(selected_data);

	//debugging
		// std::cout << "\tFiltering table: " << table_name << std::endl;
		// std::cout << "\tCondition: " << condition << std::endl;
		// std::cout << "\tNumber of rows before filtering: " << input_table.getTableData().get_size() << std::endl;

		return selected_table;
	}

bool evaluateCondition(const Cell& cell, String op, String value) {
		if(DEBUG) {
			std::cout << "[DEBUG] Checking condition: " << cell.getString() << " " << op << " " << value << std::endl;
			std::cout << "[DEBUG] DataType: " << static_cast<int>(cell.getDataType()) << std::endl;
		}

		switch (cell.getDataType()) {
			case DataType::INTEGER: {
				int cellValue = cell.getInt();
				int intValue = value.toInt();
				return (op == String("=")) ? (cellValue == intValue) :
				       (op == String("!=")) ? (cellValue != intValue) :
				       (op == String(">")) ? (cellValue > intValue) :
				       (op == String("<")) ? (cellValue < intValue) :
				       (op == String(">=")) ? (cellValue >= intValue) :
				       (op == String("<=")) ? (cellValue <= intValue) : false;
			}
			case DataType::DOUBLE: {
				double cellValue = cell.getDouble();
				double doubleValue = value.toDouble();
				return (op == String("=")) ? (cellValue == doubleValue) :
				       (op == String("!=")) ? (cellValue != doubleValue) :
				       (op == String(">")) ? (cellValue > doubleValue) :
				       (op == String("<")) ? (cellValue < doubleValue) :
				       (op == String(">=")) ? (cellValue >= doubleValue) :
				       (op == String("<=")) ? (cellValue <= doubleValue) : false;
			}
			case DataType::BOOLEAN: {
				bool cellValue = cell.getBoolean();
				bool boolValue = (value == String("true"));
				return (op == String("=")) ? (cellValue == boolValue) :
				       (op == String("!=")) ? (cellValue != boolValue) : false;
			}
			case DataType::STRING: {
				return (op == String("=")) ? (cell.getString() == value) :
				       (op == String("!=")) ? (cell.getString() != value) :
				       (op == String("LIKE")) ? (cell.getString().findSubstring(value) != -1) : false;
			}
			default:
				std::cerr << "[ERROR] Unknown DataType encountered!" << std::endl;
				return false;
		}
	}

	bool evaluateComplexCondition(const Vector<Cell>& row, Vector<int> condition_indices, Vector<String> condition_ops, Vector<String> condition_values, Vector<String> logical_ops) {
		// cout<<"INSIDE evaluateComplexCondition \t"<<endl;
		if (condition_indices.get_size() == 0) return true;

		bool result = evaluateCondition(row[condition_indices[0]], condition_ops[0], condition_values[0]);
		for (size_t i = 1; i < condition_indices.get_size(); i++) {
			bool next_result = evaluateCondition(row[condition_indices[i]], condition_ops[i], condition_values[i]);
			if (logical_ops[i - 1] == String("AND")) {
				result = result && next_result;
			} else if (logical_ops[i - 1] == String("OR")) {
				result = result || next_result;
			}
		}
		if(DEBUG) cout<<"[DEBUG] Evaluation Result: "<<result<<endl;
		return result;
	}

	// Getters
	Vector<Table>& get_tables() {return tables;}
	Vector<Vector<String>>& get_allUserPermissionsInfo() {return allUserPermissionsInfo;}
	Vector<String>& get_currentUserPermissions() {return currentUserPermissions;}

	// these are for pk and fk
	// Method to check if primary key value exists
    bool primaryKeyExists(Table* table, const Vector<Cell>& row) {
        for (int i = 0; i < table->getPrimaryKeyIndices().get_size(); ++i) {
			Vector<Vector<Cell>> table_data = table->getTableData();
			int table_data_size = table_data.get_size();
            for (int j = 0; j < table_data_size; ++j) {
                if (table_data[j][table->getPrimaryKeyIndices()[i]].getData() == row[table->getPrimaryKeyIndices()[i]].getData()) {
                    return true; // Duplicate primary key found
                }
            }
        }
        return false;
    }

    // Method to check if foreign key value exists in referenced table
    bool foreignKeyExists(Table *table, int col_index, const String& value) {
        String referenced_table_name = table->getForeignKeyIndices()[0].second;
		// ekhane 0 deyar karon tablecreation logic e forKeyExist e push_back kora hoise rather than saving at that particular col_index
        // Retrieve the referenced table and check for matching primary key
        // Assuming 'get_table_by_name' retrieves a table by name (implement as needed)
        Table ref_table = get_table_by_name(referenced_table_name);
		Vector<Vector<Cell>> ref_table_data = ref_table.getTableData();
		int ref_table_data_size = ref_table_data.get_size();

        for (int i = 0; i < ref_table_data_size; ++i) {
            if (ref_table_data[i][ref_table.getPrimaryKeyIndices()[0]].getData() == value) {
                return true;
            }
        }
        return false;
    }

	// Helper method to get the referenced table by name
    Table get_table_by_name(const String& table_name) {
        // You would need to implement a way to get the table by name from the database or from stored tables
		int tables_size = tables.get_size();
		for (int i=0; i<tables_size; i++) {
			if (tables[i].getTableName() == table_name) {
				return tables[i];
			}
		}

		// if no table by the given name has been found
		std::cout << "No table found by the following name : " << table_name << std::endl;
        return Table(); // Placeholder implementation
    }

/*bool dropTable(const String& table_name, const String& option = "CASCADE") {
        // Find the table by name
        int tableIndex = -1;
        for (int i = 0; i < tables.get_size(); ++i) {
            if (tables[i].getTableName() == table_name) {
                tableIndex = i;
                break;
            }
        }

        // If table not found, return false
        if (tableIndex == -1) {
            std::cerr << "Error: Table " << table_name << " not found." << std::endl;
            return false;
        }

        Table tableToDrop = tables[tableIndex];

        // CASCADE: Find and delete rows in other tables that reference the table being dropped
        if (option == String("CASCADE")) {
            for (int i = 0; i < tables.get_size(); ++i) {
                if (tables[i].getTableName() != table_name) {
                    // Check for foreign key references to the table being dropped
                    Vector<pair<int, String>> foreignKeys = tables[i].getForeignKeyIndices();
                    for (auto& foreignKey : foreignKeys) {
                        if (foreignKey.second == table_name) {
                            // Delete rows in the current table that reference the dropped table
                            deleteFrom(tables[i].getTableName(), "foreign_key_column = " + table_name);
                        }
                    }
                }
            }
        }

        // SET_NULL: Set the foreign key references to NULL in other tables
        if (option == String("SET_NULL")) {
            for (int i = 0; i < tables.get_size(); ++i) {
                if (tables[i].getTableName() != table_name) {
                    // Check for foreign key references to the table being dropped
                    Vector<pair<int, String>> foreignKeys = tables[i].getForeignKeyIndices();
                    for (auto& foreignKey : foreignKeys) {
                        if (foreignKey.second == table_name) {
                            // Set foreign key references to NULL in the current table
                            String condition = "foreign_key_column = " + table_name;
                            updateForeignKeyToNull(tables[i], foreignKey.first, condition);
                        }
                    }
                }
            }
        }

        // Remove the table from the internal vector
        tables.erase(tableIndex);

        // Delete the associated CSV file
        FileHandler tableFile(db_path + "/" + table_name + ".csv");
        if (tableFile.fileExists()) {
            tableFile.removeFile();
        }

        std::cout << "Table " << table_name << " has been dropped successfully." << std::endl;
        return true;
    }*/

    // Helper function to set foreign keys to NULL in a given table
/*void updateForeignKeyToNull(Table& table, int foreignKeyColumn, const String& condition) {
        Vector<Vector<Cell>> updatedData;
        for (const auto& row : table.getTableData()) {
            Vector<Cell> updatedRow = row;

            // Set the foreign key value to NULL
            updatedRow[foreignKeyColumn] = Cell();  // Assuming Cell() represents NULL

            updatedData.push_back(updatedRow);
        }

        // Update the table data
        table.updateRecords(updatedData);
        }*/
};

#endif

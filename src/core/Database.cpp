#include "../../include/PicoDB/Database.h"

// #include "../../include/PicoDB/Database.h"

// Database::Database(String db_name, String db_path, String username, String key, String table_delimiter){
// 	this->db_name = db_name;
// 	this->db_path = db_path;
// 	this->currentUser = username;
// 	this->key = key;
// 	this->delimiter = table_delimiter;
// 	this->admin = username;
// 	//check if file exists
// 	FileHandler conf_file = FileHandler(db_path+String("/")+db_name+String(".config")); //path to config file
// 	if(conf_file.fileExists()){

// 		// Conf manager fetches raw data ✅
// 		ConfigManager conf_manager(db_path+String("/")+db_name+String(".config"));

// 		// convert the config file into variables ✅
// 		this->delimiter = conf_manager.get_t_delimiter();
// 		this->admin = conf_manager.get_admin();
// 		this->allUserPermissionsInfo = conf_manager.get_permissions();

// 		// check if the user exists ✅
// 		bool user_exists = false;

// 		if (!isAdmin()) {
// 			int permissions_size = allUserPermissionsInfo.get_size();
// 			for (int i=0; i<permissions_size; i+=2) {
// 				if (username == allUserPermissionsInfo[i][0]) {
		
// 		// check if the user exists ✅
// 		bool user_exists = false;
		
// 		if (!isAdmin()) {
// 			int permissions_size = allUserPermissionsInfo.get_size(); 
// 			for (int i=0; i<permissions_size; i+=2) {
// 				if (username == allUserPermissionsInfo[i][0]) { 
// 					// we're taking [i][0] and i+=2 cause every 2nd vector in allUserPermissionInfo contains the table name, need to use constants here later
// 					Vector<String> temp = allUserPermissionsInfo[i+1];
// 					this->currentUserPermissions = temp;
// 					user_exists = true;
// 					break;
// 				}
// 			}
// 		}

// 		if (user_exists || isAdmin()) {
// 			//convert the tables into vector ✅
// 			loadCurrentTables(conf_manager);
// 		} else {
// 			// throw exception
// 		}

// 	}
// 	else{
// 		//create config file
// 		ConfigManager conf_manager(db_path+String("/")+db_name+".config");
// 		conf_manager.createConfig(db_name,table_delimiter,username, true);
// 	}
// }

// void Database::update(String table_name, Vector<String>update_data, Vector<int >condition){
// 	Table table;
// 	for(int i=0;i<tables.get_size();i++){
// 		if(tables[i].getTableName() == table_name){
// 			table = tables[i];
// 			break;
// 		}
// 		else{
// 			//add exception
// 		}
// 	}
// 	//check condition
// 	// Table condition_data;
// 	// if(condition[1]=="=="){
// 	// 	for(int i=0;i<table.get_RowSize();i++){
// 	// 		for(int j=0;j<table[i].;j++){
// 	// 		}
// 	// 	}
// 	// }
// 	// else if(condition[1]==">"){

// 	// }
// 	// else if(condition[1]=="<"){

// 	// }
// 	// else if(condition[1]==">="){

// 	// }
// 	// else if(condition[1]=="<="){

// 	// }
// 	// else if(condition[1]=="!="){

// 	// }
// 	// else{
// 	// 	//exception
// 	// }
// }

// void Database::loadCurrentTables(ConfigManager conf_manager){
// 	ConfigManager conf_file = conf_manager;
// 	StringVectorConverter converter;
// 	Encryptor encryptor(String(key).toInt());

// 	// fetch the config file data and add it to table_name, headers, types and constraints
// 	Vector<Vector<String>> temp_data = conf_file.get_table_meta_data();
// 	int temp_data_size = temp_data.get_size();

// 	if (!isAdmin()) {
// 		for(int i=0; i<temp_data_size; i+=4) {
// 			int current_permission_size = currentUserPermissions.get_size();
// 			for (int j=0; j<current_permission_size; j++) {
// 				if (temp_data[i][0] == currentUserPermissions[j]){
// 					this->tables.push_back(Table(temp_data[i][0],temp_data[i+1],temp_data[i+2],temp_data[i+3]));
// 				}
// 			}
// 		}

// 	} else {
// 		for(int i=0; i<temp_data_size; i+=4) {
// 			this->tables.push_back(Table(temp_data[i][0],temp_data[i+1],temp_data[i+2],temp_data[i+3]));
// 		}
// 	}

// 	// decrypt the csv file data related to the table and copy the info
// 	int table_size = tables.get_size();
// 	for(int i=0; i<table_size; i++) {
// 		String table_name = tables[i].getTableName();
// 		Vector<String> data_types = tables[i].getDataTypes();
// 		Vector<Vector<Cell>> cell_data;
// 		Vector<Vector<String>> table_data_from_file;
// 		String table_string_data;

// 		// open the specific table file and decrypt it
// 		FileHandler table_file = FileHandler(db_path+String("/")+table_name+String(".csv")); //path to that table's csv file
// 		table_string_data = table_file.readFromFile();
// 		table_string_data = encryptor.decryptData(table_string_data); // decrypt fetched string data


// 		//converter.stringToVector(table_string_data, delimiter);
// 		table_data_from_file = converter.stringToVector(table_string_data, delimiter);



		
// 		//converter.stringToVector(table_string_data, delimiter);
// 		table_data_from_file = converter.stringToVector(table_string_data, delimiter);

		

// 		// load the data to table cells
// 		int num_of_types = data_types.get_size();
// 		int num_of_rows = table_data_from_file.get_size();
// 		for (int j=0; j<num_of_rows; j++) {
// 			Vector<Cell> single_line_cell_data;
// 			for (int k=0; k<num_of_types; k++) {
// 				if (data_types[k] == String("INT")) {
// 					// Conversion to int
// 					single_line_cell_data.push_back(Cell(table_data_from_file[j][k].toInt()));
// 				} else if (data_types[k] == String("DOUBLE")) {
// 					// Conversion to double
// 					single_line_cell_data.push_back(Cell(table_data_from_file[j][k].toDouble()));
// 				} else if (data_types[k] == String("BOOLEAN")) {
// 					// Conversion to boolean
// 					// single_line_cell_data.push_back(Cell(table_data_from_file[j][k].toBool()));
// 				} else {
// 					// Default case (e.g., assume it's a string)
// 					single_line_cell_data.push_back(Cell(table_data_from_file[j][k]));
// 				}
// 			}
// 			cell_data.push_back(single_line_cell_data);
// 		}
// 		tables[i].updateRecords(cell_data);
// 	}
// }

// bool Database::isAdmin() {
// return this->currentUser == this->admin; // Compares the current user with the stored admin username
// }


// void Database::saveTableData(){
// 	int table_size = tables.get_size();
// 	for (int i=0; i<table_size; i++) {
// 		String table_name = tables[i].getTableName();
// 		int num_columns = tables[i].getHeaders().get_size();

// 		Vector<Vector<Cell>> cells = tables[i].getTableData();
// 		Vector<Vector<String>> table_data;

// 		int num_rows = cells.get_size();
// 		for (int j=0; j<num_rows; j++) {
// 			Vector<String> row_data;
// 			for (int k=0; k<num_columns; k++) {
// 				DataType dataType = cells[j][k].getDataType();

// 				if (dataType == DataType::INTEGER) {
// 					// conversion from int to string
// 					row_data.push_back(String::toString(cells[j][k].getInt()));
// 				} else if (dataType == DataType::DOUBLE) {
// 					// conversion from double to string
// 					row_data.push_back(String::toString(cells[j][k].getDouble()));
// 				} else if (dataType == DataType::BOOLEAN) {
// 					// conversion from boolean to string
// 					row_data.push_back(String::toString(cells[j][k].getBoolean()));
// 				} else {
// 					// code to execute if none of the cases match
// 					row_data.push_back(cells[j][k].getString());
// 				}
// 			}
// 			table_data.push_back(row_data);
// 		}

// 		StringVectorConverter converter;
// 		Encryptor encryptor(String(key).toInt());

// 		String file_data = converter.vector2DToString(table_data, delimiter);  // converts vector data to string for writing
// 		file_data = encryptor.encryptData(file_data);   // encrypts the data

// 		FileHandler table_file(db_path+String("/")+table_name+String(".csv")); //path to that table's csv file

// 		table_file.createFile();
// 		table_file.writeToFile(file_data);
// 	}
// }

// void Database::saveDBMetaData() {
// 	StringVectorConverter converter;
// 	String conf_data;
// 	conf_data+=String("[Database]\n");
// 	conf_data+=String("database_name = ") + db_name + String("\n"); //Check
// 	conf_data+=String("file_path = ") + db_path+String("/")+ db_name + ".config" + String("\n");
// 	conf_data+=String("table_delimiter = ") + delimiter + String("\n");
// 	conf_data+=String("\n");
// 	conf_data+=String("[Admin]\n");
// 	conf_data+=String("username = ") + admin + String("\n");
// 	conf_data+=String("\n");
// 	conf_data+=String("[Permission]\n");
// 	conf_data+= converter.vector2DToString(allUserPermissionsInfo, ",");
// 	conf_data+=String("\n");
// 	conf_data+=String("\n");
// 	conf_data+=String("[Encryption]\n");
// 	if(encryption) conf_data+=String("enabled = true\n");
// 	else conf_data+=String("enabled = false\n");
// 	conf_data+=String("\n");
// 	conf_data+=String("[Tables]\n");

// 	String table_metadata = TableMetaData();
// 	conf_data += table_metadata;

// 	ConfigManager conf_manager(db_path+String("/")+db_name+String(".config"));
// 	conf_manager.updateConfig(conf_data);

// 	// FileHandler config_file(db_path+String("/")+db_name+String(".config"));

// 	// config_file.createFile();
// 	// config_file.writeToFile(conf_data);
// }

// String Database::TableMetaData(){
// 	String table_meta_data;
// 	StringVectorConverter converter;
// 	ConfigManager conf_manager(db_path+String("/")+db_name+String(".config"));

// 	if (isAdmin()) {
// 		int tables_num = tables.get_size();
// 		for(int i=0; i<tables_num; i++) {
// 			//for table names
// 			table_meta_data += tables[i].getTableName();
// 			table_meta_data += String("\n");

// 			//for headers
// 			table_meta_data += converter.vectorToString(tables[i].getHeaders());

// 			//for data_types
// 			table_meta_data += converter.vectorToString(tables[i].getDataTypes());

// 			//for constraints
// 			table_meta_data += converter.vectorToString(tables[i].getConstraints());
// 		}
// 	} else {
// 		Vector<Vector<String>> temp_table_meta_data = conf_manager.get_table_meta_data();

// 		int temp_table_meta_data_size = temp_table_meta_data.get_size();
// 		int tables_num = tables.get_size();
// 		for (int i=0; i<tables_num; i++) {
// 			for (int j=0; j<temp_table_meta_data_size; j+=4) {
// 				if (tables[i].getTableName() == temp_table_meta_data[j][0]) {
// 					temp_table_meta_data[j+1] = tables[i].getHeaders();
// 					temp_table_meta_data[j+2] = tables[i].getDataTypes();
// 					temp_table_meta_data[j+3] = tables[i].getConstraints();
// 				}
// 			}
// 		}

// 		table_meta_data += converter.vector2DToString(temp_table_meta_data, delimiter);
// 	}
// 	return table_meta_data;
// }

// bool Database::saveDB(){
// 	saveDBMetaData();
// 	saveTableData();
// 	return true;
// }

// bool Database::insertInto(String table_name, Vector<String> cols, Vector<String> cell_data) {
// 	int tables_num = tables.get_size();

// 	for (int i = 0; i < tables_num; i++) {
// 		if (table_name == tables[i].getTableName()) {
// 			Vector<String> data_types = tables[i].getDataTypes();
// 			Vector<String> headers = tables[i].getHeaders();
// 			int num_of_columns = headers.get_size();

// 			// Check if cols and cell_data match the table's headers
// 			if (cols.get_size() != cell_data.get_size() || cols.get_size() > num_of_columns) {
// 				cout << "Error: Column and data size mismatch." << endl;
// 				cout << "Expected columns: " << num_of_columns << ", but got: " << cols.get_size() << endl;
// 				return false;
// 			}

// 			Vector<Cell> single_line_cell_data;

// 			for (int j = 0; j < num_of_columns; j++) {
// 				bool column_matched = false;

// 				// Check if headers[j] exists in cols
// 				for (int k = 0; k < cols.get_size(); k++) {
// 					if (headers[j] == cols[k]) {
// 						column_matched = true;

// 						// Add cell data according to the data type
// 						if (data_types[j] == String("INT")) {
// 							single_line_cell_data.push_back(Cell(cell_data[k].toInt()));
// 						} else if (data_types[j] == String("DOUBLE")) {
// 							single_line_cell_data.push_back(Cell(cell_data[k].toDouble()));
// 						} else if (data_types[j] == String("BOOLEAN")) {
// 							//single_line_cell_data.push_back(Cell(cell_data[k].toBool()));
// 						} else {
// 							single_line_cell_data.push_back(Cell(cell_data[k]));
// 						}
// 						break;
// 					}
// 				}

// 				// If column not found in cols, add a default value or handle as needed
// 				if (!column_matched) {
// 					cout << "Warning: Column " << headers[j] << " not found in input cols. Adding default value." << endl;
// 					single_line_cell_data.push_back(Cell());  // Assuming default constructor in Cell
// 				}
// 			}

// 			// Update the table with the new row data
// 			tables[i].updateSingleRecord(single_line_cell_data);
// 			return true;  // Insertion successful
// 		}
// 	}

// 	// Table not found
// 	cout << "Error: Table " << table_name << " not found." << endl;
// 	return false;
// }

//function for printing a table
// void Database::printTable(const Table& table) {
// 	// Print table name
// 	std::cout << "Table: " << table.getTableName() << std::endl;

// 	// Get the column headers
// 	Vector<String> headers = table.getHeaders();

// 	// Determine the maximum width for each column
// 	Vector<size_t> colWidths;
// 	for (int i = 0; i < headers.get_size(); ++i) {
// 		colWidths.push_back(0); // Initialize each element to 0
// 	}

// 	// First, calculate the maximum length of each column (header + data)
// 	for (int i = 0; i < headers.get_size(); ++i) {
// 		colWidths[i] = headers[i].length();  // Start by considering the header size
// 	}

// 	// Also check the row data for each column to find the longest string in that column
// 	Vector<Vector<Cell>> rows = table.getTableData();
// 	for (int i = 0; i < rows.get_size(); ++i) {
// 		for (int j = 0; j < rows[i].get_size(); ++j) {
// 			//size_t cellLength = rows[i][j].getString().length();
// 			size_t cellLength ;
// 			String c_data;
// 			DataType dataType = rows[i][j].getDataType();

// 			if (dataType == DataType::INTEGER) {
// 				// conversion from int to string
// 				c_data = String::toString(rows[i][j].getInt());
// 			} else if (dataType == DataType::DOUBLE) {
// 				// conversion from double to string
// 				c_data = String::toString(rows[i][j].getDouble());
// 			} else if (dataType == DataType::BOOLEAN) {
// 				// conversion from boolean to string
// 				c_data = String::toString(rows[i][j].getBoolean());
// 			} else {
// 				// code to execute if none of the cases match
// 				c_data = rows[i][j].getString();
// 			}

// 			cellLength = c_data.length();
// 			if (cellLength > colWidths[j]) {
// 				colWidths[j] = cellLength;  // Update column width if the cell's length is greater
// 			}
// 		}
// 	}
// 	// --- Added roof line here ---
// 	for (int i = 0; i < headers.get_size(); ++i) {
// 		std::cout << "+";
// 		for (size_t j = 0; j < colWidths[i] + 2; ++j) {
// 			std::cout << "-";  // Create a separator line with appropriate width
// 		}
// 	}
// 	std::cout << "+" << std::endl;  // End line for the roof
// 	// --- End of roof line ---

// 	// Print column headers with dynamic widths
// 	for (int i = 0; i < headers.get_size(); ++i) {
// 		std::cout << "| " << headers[i];
// 		// Pad the header to match the max width
// 		for (size_t j = headers[i].length(); j < colWidths[i]; ++j) {
// 			std::cout << " ";
// 		}
// 		std::cout << " ";  // Space after each column
// 	}
// 	std::cout << "|" << std::endl;

// 	// Print a line under the headers to form a box
// 	for (int i = 0; i < headers.get_size(); ++i) {
// 		std::cout << "+";
// 		for (size_t j = 0; j < colWidths[i] + 2; ++j) {
// 			std::cout << "-";  // Create a separator line with appropriate width
// 		}
// 	}
// 	std::cout << "+" << std::endl;

// 	// Print rows with dynamic column widths
// 	if (rows.get_size() == 0) {
// 		std::cout << "No records found." << std::endl;
// 	} else {
// 		for (int i = 0; i < rows.get_size(); ++i) {
// 			for (int j = 0; j < rows[i].get_size(); ++j) {
// 				String cell_data;
// 				DataType dataType = rows[i][j].getDataType();

// 				if (dataType == DataType::INTEGER) {
// 					// conversion from int to string
// 					cell_data = String::toString(rows[i][j].getInt());
// 				} else if (dataType == DataType::DOUBLE) {
// 					// conversion from double to string
// 					cell_data = String::toString(rows[i][j].getDouble());
// 				} else if (dataType == DataType::BOOLEAN) {
// 					// conversion from boolean to string
// 					cell_data = String::toString(rows[i][j].getBoolean());
// 				} else {
// 					// code to execute if none of the cases match
// 					cell_data = rows[i][j].getString();
// 				}

// 				std::cout << "| " << cell_data;
// 				// Pad each column to the dynamic width
// 				for (size_t k = cell_data.length(); k < colWidths[j]; ++k) {
// 					std::cout << " ";
// 				}
// 				std::cout << " ";  // Space after each column
// 			}
// 			std::cout << "|" << std::endl;
// 		}
// 	}

// 	// Print bottom line to close the box
// 	for (int i = 0; i < headers.get_size(); ++i) {
// 		std::cout << "+";
// 		for (size_t j = 0; j < colWidths[i] + 2; ++j) {
// 			std::cout << "-";  // Closing line for each column
// 		}
// 	}
// 	std::cout << "+" << std::endl;  // End line for the bottom of the table
// }

//getter for tables
// Vector<Table>& Database::get_tables() {
// 	return tables;
// }

// Vector<Vector<String>>& Database::get_allUserPermissionsInfo() {
// 	return allUserPermissionsInfo;
// }

// Vector<String>& Database::get_currentUserPermissions() {
// 	return currentUserPermissions;
// }

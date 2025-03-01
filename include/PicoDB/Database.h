#ifndef DATABASE_H // Include guard start
#define DATABASE_H
#include<iostream>
#include<filesystem>
#include "Vector.h"
#include "Encryptor.h"
#include "String.h"
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
	// Vector<>permissions;
public:

	// Database(string db_name, bool force_create, bool encryption, string file_path )
	Database(String db_name, String db_path, String username, String key, String table_delimiter = String(";_;pico;_;")){
		this->db_name = db_name;
		this->db_path = db_path;
		this->username = username;
		this->key = key;
		this->delimiter = delimiter;
		this->admin = username;
		//check if file exists
		FileHandler conf_file = FileHandler(db_path+String("/")+db_name+String(".config")); //path to config file
		if(conf_file.fileExists()){

			// Conf manager fetches raw data ✅
			ConfigManager conf_manager(db_path+String("/")+db_name+String(".config"));

			// convert the config file into variables
			this->delimiter = conf_manager.get_t_delimiter();
			this->admin = conf_manager.get_admin();
			//this->db_data = conf_manager.get_table_header();
			// TODO : must check if the user exists

			//convert the tables into vector ✅
			//loadCurrentTables(db_name, db_path);

		}
		else{
			//create config file
			ConfigManager conf_manager(db_path+String("/")+db_name+".config");
			conf_manager.createConfig(db_name,table_delimiter,username );
		}
	};
	// Database e(string db_name, bool encryption);

	void loadCurrentTables(String database_name, String file_path){
		ConfigManager conf_file(file_path+String("/")+database_name+String(".config"));
		StringVectorConverter converter;
		Encryptor encryptor(String(key).toInt());

		// fetch the config file data and add it to table_name, headers, types and constraints
		Vector<Vector<String>> temp_data = conf_file.get_table_meta_data();
		int temp_data_size = temp_data.get_size();
		for(int i=0; i<temp_data_size; i+=4) {
			this->tables.push_back(Table(temp_data[i][0],temp_data[i+1],temp_data[i+2],temp_data[i+3]));
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
						// single_line_cell_data.push_back(Cell(table_data_from_file[j][k].toBool()));
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

	//void saveDBMetaData() {}

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
					table_data.push_back(row_data);
				}
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

	void saveTableMetaData(){
		String table_meta_data;
		StringVectorConverter converter;
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

		ConfigManager conf_manager(db_path+String("/")+db_name+String(".config"));
		conf_manager.appendConfig(table_meta_data, true);
	}

	bool saveDB(){
		saveTableMetaData();
		saveTableData();
		return true;
		//saveDBMetaData();
	}

	bool insertInto(String table_name, Vector<String> cols, Vector<String> cell_data) {
		int tables_num = tables.get_size();

		for (int i = 0; i < tables_num; i++) {
			if (table_name == tables[i].getTableName()) {
				Vector<String> data_types = tables[i].getDataTypes();
				Vector<String> headers = tables[i].getHeaders();
				int num_of_columns = headers.get_size();

				// Check if cols and cell_data match the table's headers
				if (cols.get_size() != cell_data.get_size() || cols.get_size() > num_of_columns) {
					cout << "Error: Column and data size mismatch." << endl;
					cout << "Expected columns: " << num_of_columns << ", but got: " << cols.get_size() << endl;
					return false;
				}

				Vector<Cell> single_line_cell_data;

				for (int j = 0; j < num_of_columns; j++) {
					bool column_matched = false;

					// Check if headers[j] exists in cols
					for (int k = 0; k < cols.get_size(); k++) {
						if (headers[j] == cols[k]) {
							column_matched = true;

							// Debug output
							cout << "Matching column " << headers[j] << " with data " << cell_data[k] << endl;

							// Add cell data according to the data type
							if (data_types[j] == String("INT")) {
								single_line_cell_data.push_back(Cell(cell_data[k].toInt()));
							} else if (data_types[j] == String("DOUBLE")) {
								single_line_cell_data.push_back(Cell(cell_data[k].toDouble()));
							} else if (data_types[j] == String("BOOLEAN")) {
								//single_line_cell_data.push_back(Cell(cell_data[k].toBool()));
							} else {
								single_line_cell_data.push_back(Cell(cell_data[k]));
							}
							break;
						}
					}

					// If column not found in cols, add a default value or handle as needed
					if (!column_matched) {
						cout << "Warning: Column " << headers[j] << " not found in input cols. Adding default value." << endl;
						single_line_cell_data.push_back(Cell());  // Assuming default constructor in Cell
					}
				}

				// Update the table with the new row data
				tables[i].updateSingleRecord(single_line_cell_data);
				return true;  // Insertion successful
			}
		}

		// Table not found
		cout << "Error: Table " << table_name << " not found." << endl;
		return false;
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

	//getter for tables
	Vector<Table>& get_tables() {
		return tables;
}

Table select(String table_name, Vector<String> cols, String condition) {
if(DEBUG) cout << "[DEBUG] Searching for table: " << table_name << std::endl;
    Table input_table;
    bool table_found = false;

    // Find the table by name

    for (int i = 0; i < tables.get_size(); i++) {
    if(DEBUG) cout << "[DEBUG] Checking table: " << tables[i].getTableName() << std::endl;
        if (tables[i].getTableName() == table_name) {
            input_table = tables[i];
            table_found = true;
            if(DEBUG) cout << "[DEBUG] Table found!" << std::endl;
            break;
        }
    }
    if(DEBUG) cout<<endl;

    if (!table_found) {
        std::cerr << "Table not found: " << table_name << std::endl;
        return Table();
    }

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
    if(DEBUG) cout<<"INSIDE evaluateCondition"<<endl;
    if(DEBUG) std::cout << "Checking condition: " << cell.getString() << " " << op << " " << value << std::endl;
    if (cell.getDataType() == DataType::INTEGER) {
        int cellValue = cell.getInt();
        int intValue = value.toInt();
        if (op == String("=")) return cellValue == intValue;
        if (op == String("!=")) return cellValue != intValue;
        if (op == String(">")) return cellValue > intValue;
        if (op == String("<")) return cellValue < intValue;
        if (op == String(">=")) return cellValue >= intValue;
        if (op == String("<=")) return cellValue <= intValue;
    } else if (cell.getDataType() == DataType::DOUBLE) {
        double cellValue = cell.getDouble();
        double doubleValue = value.toDouble();
        if (op == String("=")) return cellValue == doubleValue;
        if (op == String("!=")) return cellValue != doubleValue;
        if (op == String(">")) return cellValue > doubleValue;
        if (op == String("<")) return cellValue < doubleValue;
        if (op == String(">=")) return cellValue >= doubleValue;
        if (op == String("<=")) return cellValue <= doubleValue;
    } else if (cell.getDataType() == DataType::BOOLEAN) {
        bool cellValue = cell.getBoolean();
        bool boolValue = (value == String("true"));
        return (op == String("=")) ? (cellValue == boolValue) : (cellValue != boolValue);
    } else {
        if (op == String("=")) return cell.getString() == value;
        if (op == String("!=")) return cell.getString() != value;
        if (op == String("LIKE")) return cell.getString().findSubstring(value) != -1;
    }
    return false;
}

bool evaluateComplexCondition(const Vector<Cell>& row, Vector<int> condition_indices, Vector<String> condition_ops, Vector<String> condition_values, Vector<String> logical_ops) {
    // cout<<"INSIDE evaluateComplexCondition \t"<<(condition_indices.get_size() == 0)<<endl;
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

    return result;
}


};
#endif

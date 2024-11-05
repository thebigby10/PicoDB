#ifndef DATABASE_H // Include guard start
#define DATABASE_H
#include<iostream>
#include<filesystem>
#include "Vector.cpp"
#include "Encryptor.cpp"
#include "String.cpp"
#include "Table.cpp"
#include "FileHandler.cpp"
#include "Cell.cpp"
#include "ConfigManager.cpp"
#include "StringVectorConverter.cpp"

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
			loadCurrentTables(db_name, db_path);
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
                for (int k=0; k<num_columns; k++) {
                    Vector<String> row_data;
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
		//saveDBMetaData();
	}

	//getter for tables
	Vector<Table> get_tables() {
		return tables;
	}

};
#endif

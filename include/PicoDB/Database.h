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

	void update(String table_name, Vector<String>update_data, Vector<int >condition);


	void loadCurrentTables(String database_name, String file_path);

	//void saveDBMetaData() {}

	void saveTableData();

	void saveTableMetaData();

	bool saveDB();

	bool insertInto(String table_name, Vector<String> cols, Vector<String> cell_data);

	//function for printing a table
	void printTable(const Table& table) ;

	//getter for tables
	Vector<Table>& get_tables();

	Table select(String table_name, Vector<String> cols, String condition = "")
};
#endif

#include<iostream>
#include<filesystem>
#include "Vector.cpp"
#include "String.cpp"
// #include "Table.cpp"
#include "FileHandler.cpp"
#include "ConfigManager.cpp"

class Database{
private:
	String db_name; 
	String db_path;
	String username;
	String key;
	String delimiter;
	bool encryption = true;
	// Vector<Table> db_data;
public:

	// Database(string db_name, bool force_create, bool encryption, string file_path )
	Database(String db_name, String db_path, String username, String key, String table_delimiter = String(";_;pico;_;")){
		this->db_name = db_name;
		this->db_path = db_path;
		this->username = username;
		this->key = key;
		this->delimiter = delimiter;
		//check if file exists
		FileHandler conf_file = FileHandler(db_path+String("/")+db_name+String(".config")); //path to config file
		if(conf_file.fileExists()){
// Conf manager fetches raw data ✅
			ConfigManager conf_manager(conf_file);
			// convert the config file into variables
			// TODO : must check if the user exists
//	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO	TODO
			//convert the tables into vector
		}
		else{
			//create config file
			ConfigManager conf_manager(db_path+String("/")+db_name+".config");
			conf_manager.createConfig(db_name,table_delimiter,username );
		}
	};
	// Databas e(string db_name, bool encryption);
private:
	string db_name; 
	string file_path = "";
	bool encryption = true;
	vector<Table> db_data;
};
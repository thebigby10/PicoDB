#include<iostream>
#include<filesystem>
#include "Vector.cpp"
#include "String.cpp"
#include "Table.cpp"
#include "FileHandler.cpp"
#include "ConfigManager.cpp"
using namespace std;

class Database{
public:
	// Database(string db_name, bool force_create, bool encryption, string file_path )
	Database(String db_name, String db_path, String username, String key){
		//check if file exists
		FileHandler db_file = FileHandler(db_path+String("/")+db_name+String(".config")); //path to config file
		if(db_file.fileExists()){
			// fetch config file
			
			// fetch raw data
			// decrypt the data
			// convert decrypte raw data to vector 3/table
		}
		else{
			//create config file
			ConfigManager conf_manager(db_path);
			Vector< Map<String, String> > conf_data = conf_manager.writeConfig();
		}
	};
	// Databas e(string db_name, bool encryption);
private:
	string db_name; 
	string file_path = "";
	bool encryption = true;
	vector<Table> db_data;
};
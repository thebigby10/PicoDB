#include<iostream>
#include<filesystem>
#include "Vector.cpp"
#include <String.cpp>
#include "Table.cpp"
#include "FileUtils.cpp"
using namespace std;

class Database{
public:
	// Database(string db_name, bool force_create, bool encryption, string file_path )
	Database(String db_name, String db_path, String username, String key){
		//check if file exists
		bool exists;
		if(fileExists(db_path)){
			//directly
			//fetch all data : use filehandler class
			//convert it into a 3d vector data
			
		}
		else{
			//create config file
		}
	};
	// Databas e(string db_name, bool encryption);
private:
	string db_name; 
	string file_path = "";
	bool encryption = true;
	vector<Table> db_data;
};
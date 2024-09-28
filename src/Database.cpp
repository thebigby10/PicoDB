#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include "Table.cpp"
using namespace std;

class Database{
public:
	// Database(string db_name, bool force_create, bool encryption, string file_path )
	Database(string db_name, string db_path){
		//check if file exists
		bool exists;
		if(exists){
			//directly
			//fetch all data : use filehandler class
			//convert it into a 3d vector data
		}
		else{
			//create config file
		}
	};
	// Database(string db_name, bool encryption);
private:
	string db_name; 
	string file_path = "";
	bool encryption = true;
	vector<Table> db_data;
};
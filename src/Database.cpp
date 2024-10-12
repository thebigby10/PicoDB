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
	Database(string db_name, bool encryption){
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
	}

	bool createTable(string table_name,vector<vector<string > > col_data ){ 
		//add conditions
		row_data[][0] = col_name
		row_data[][1] = type
		row_data[][2] = constrains
		row_data[][3] = conditions
	}
	
private:
	string db_name; 
	string file_path = "";
	bool encryption = true;
	vector<Table> db_data;

	
};
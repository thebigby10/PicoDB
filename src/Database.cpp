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

	bool createTable(string tableName, vector < vector <string> > columnData) {
    // Create a 2D vector to store column data
    vector < vector <string> > table;

    // Add each column definition to the table
    for (const auto& column : columnData) {
        table.push_back(column);
    }

    // Add the table to the database 
    db_data.push_back(table); // this vector is 3D

    // Simulate saving table info
    cout << "Table '" << tableName << "' created successfully with the following columns:" << endl;
    for (const auto& column : columnData) {
        cout << "Column: " << column[0] << " | Type: " << column[1] << " | Constraints: ";
        for (size_t i = 2; i < column.size(); ++i) {
            cout << column[i] << " ";
        }
        cout << endl;
    }

    // Assume table creation is always successful for now
    return true;
}
	
private:
	string db_name; 
	string file_path = "";
	bool encryption = true;
	vector < vector < vector <string> > > db_data; //3d
	

	
};
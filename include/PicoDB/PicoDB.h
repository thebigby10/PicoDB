#include<iostream>

#include "../../src/Database.cpp"
#include "../../src/Table.cpp"
#include "../../src/Cell.cpp"

#include "../../src/FileHandler.cpp"
#include "../../src/Encryptor.cpp"

#include "../../src/Vector.cpp"
// #include "../../src/Date.cpp"

#include "../../src/String.cpp"
#include "../../src/Map.cpp"

class PicoDB{
private:
	Database db;

public:
	PicoDB(String db_name, String db_path, String username, String key, String table_delimiter)
    	: db(db_name, db_path, username, key, table_delimiter) {
    		// Constructor body can remain empty if no additional setup is needed
	}

	PicoDB(String db_name, String db_path, String username, String key)
	: db(db_name, db_path, username, key) {
        	// No additional setup implemented in the constructor body yet
	}

	bool createTable(String table_name,Vector<Vector<String>> col_data){
		cout<<"CREATE TABLE"<<endl;
        (this->db).get_tables().push_back(Table(table_name, col_data));
        cout<<(this->db).get_tables().get_size()<<endl;
        //DEBUG
        // cout<<this->db.get_tables().get_size()<<endl;
        //DEBUG
        //todo if exists
		return true;
	}

	Table select(String table_name, Vector<String> cols){
		if(cols.get_size()==0){
			Table output_table;
			Table input_table;
			for(int i=0;i<db.get_tables().get_size();i++){
				if(db.get_tables()[i].table_name == table_name){
					input_table = db.get_tables()[i];
					break;
				}
			}
			return input_table;
		}
	}
	

	/*
	bool insertInto(string table_name, vector<string> col_data, vector<string>col_values ){

	}

	vector<vector< string > > selectData(string table_name, vector<string> cols){

	}

	vector<vector< string > > selectDataWhere(string table_name, vector<string> cols){

	}*/

	bool saveDB(){
		this->db.saveDB();
	}
	/*
	bool dropTable(){

	}
	*/
};

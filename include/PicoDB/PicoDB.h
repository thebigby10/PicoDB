#include<bits/stdc++.h>
#include "../../src/Database.cpp"
#include "../../src/Table.cpp"
#include "../../src/Cell.cpp"

#include "../../src/FileHandler.cpp"
#include "../../src/Encryptor.cpp"

#include "../../src/Vector.cpp"
#include "../../src/Date.cpp"

class PicoDB{
public:
	PicoDB(string db_name, string db_path){
		Database database(db_name, db_path);
	}
	bool createTable(string table_name,vector<vector<string > > col_data ){ //add conditios
		//row_data[][0] = col_name
		//row_data[][1] = type
		//row_data[][2] = constrains
		//row_data[][3] = conditions
	}
	bool insertData(string table_name, vector<string> col_data, vector<string>col_values ){

	} 

	vector<vector< string > > selectData(string table_name, vector<string> cols){

	}
	bool saveDB(){

	}
	bool dropTable(){
		
	}
};
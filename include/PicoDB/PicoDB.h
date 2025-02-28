#include<iostream>

#include "Database.h"
#include "Table.h"
#include "Cell.h"

#include "FileHandler.h"
#include "Encryptor.h"

#include "Vector.h"
// #include "../../src/Date.cpp"

#include "String.h"
#include "Map.h"

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

	bool createTable(String table_name, Vector<Vector<String>> col_data);

	void update(String table_name, Vector<String>update_data, Vector<int >condition);

	// bool insertInto(String table_name, Vector<String> col_data, Vector<String> col_values);
	bool insertInto(String table_name, Vector<String> col_names, Vector<String> values);


	/*
	vector<vector< string > > selectData(string table_name, vector<string> cols);

	vector<vector< string > > selectDataWhere(string table_name, vector<string> cols);*/

	bool saveDB();
	/*
	bool dropTable();
	*/

};

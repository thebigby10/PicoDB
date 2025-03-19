#ifndef PICODB_H
#define PICODB_H

#include "Database.h"
// #include "Table.h"
// #include "Cell.h"
#include "UserPermissionManager.h"
// #include "FileHandler.h"
// #include "Encryptor.h"
// #include "Vector.h"
// #include "String.h"

class PicoDB {
private:
    Database db;

public:
    PicoDB(String db_name, String db_path, String username, String key, String table_delimiter)
		: db(db_name, db_path, username, key, table_delimiter) {
			// Constructor body can remain empty if no additional setup is needed
	}

    // PicoDB(String db_name, String db_path, String username, String key)
	// : db(db_name, db_path, username, key) {
	// 		// No additional setup implemented in the constructor body yet
	// }

    bool createTable(String table_name, Vector<Vector<String>> col_data){
		return this->db.createTable(table_name, col_data);
	}

    Table select(Table table, Vector<String> cols, String condition) {
        return this->db.select(table, cols, condition);
    }

    bool update(String table_name, Vector<Vector<String>> update_values, String condition) {
        return this->db.update(table_name, update_values, condition);
    }

    bool deleteFrom(String table_name, String condition) {
        return this->db.deleteFrom(table_name, condition);
    }

    bool insertInto(String table_name, Vector<String> col_names, Vector<String> values) {
        return this->db.insertInto(table_name, col_names, values);
    }

    bool dropTable(String table_name) {
        return this->db.dropTable(table_name);
    }

    bool dropDB() {
        return this->db.dropDB();
    }

    Table getTable(String table_name){
        return this->db.get_table_by_name(table_name);
    }
    
    void addUser (const String& username, const String& tableName) {
        UserPermissionManager permissionManager(db);
        permissionManager.addUser(username, tableName);
    }

    void grantPermission(const String& username, const String& tableName) {
        UserPermissionManager permissionManager(this->db);
        permissionManager.grantPermission(username, tableName);
    }

    void revokePermission(const String& username, const String& tableName) {
        UserPermissionManager permissionManager(this->db);
        permissionManager.revokePermission(username, tableName);
    }

    bool saveDB(){
        this->db.saveDB();
        return true;
    }

    void printTable(Table& table){
        this->db.printTable(table);
	}
    // bool dropTable(){}

};

#endif // PICODB_H

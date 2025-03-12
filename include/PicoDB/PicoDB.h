#ifndef PICODB_H
#define PICODB_H

#include<iostream>
#include "Database.h"
#include "Table.h"
#include "Cell.h"
#include "FileHandler.h"
#include "Encryptor.h"
#include "Vector.h"
#include "String.h"

class PicoDB {
public:
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

    bool createTable(String table_name, Vector<Vector<String>> col_data) {
        this->db.get_tables().push_back(Table(table_name, col_data));
        return true;
    }

    bool insertInto(String table_name, Vector<String> col_names, Vector<String> values) {
        for (int i = 0; i < db.get_tables().get_size(); ++i) {
            if (db.get_tables()[i].getTableName() == table_name) {
                Table& table = db.get_tables()[i];
                // Ensure the number of columns matches the number of values
                if (col_names.get_size() == values.get_size()) {
                    Vector<Cell> row_data;
                    for (int j = 0; j < values.get_size(); ++j) {
                        // Convert values to Cell objects based on data type
                        // Assuming all values are strings for simplicity
                        row_data.push_back(Cell(values[j]));
                    }
                    table.updateSingleRecord(row_data);
                } else {
                    std::cerr << "Column count does not match value count" << std::endl;
                    return false;
                }
                return true;
            }
        }
        std::cerr << "Table not found" << std::endl;
        return false;
    }

    bool saveDB() {
        this->db.saveDB();
        return true;
    }

    Table select(String table_name, Vector<String> cols, String condition) {
        return this->db.select(table_name, cols, condition);
    }

    void printTable(Table& table) {
        this->db.printTable(table);
    }

    String getDBName() const {
        return db.get_db_name();
    }

    Vector<Table>& getTables() {
        return db.get_tables();
    }
};

#endif // PICODB_H

#ifndef TABLE_H // Include guard start
#define TABLE_H
#include<iostream>
#include "String.h"
#include "Vector.h"
#include "Cell.h"
#include <bits/stdc++.h>

using namespace std;

/*
class Constraints{
public:
	String constraint_key; // NOT_NULL, UNIQUE, PEIMARY_KEY, FOREIGN_KEY, DEFAULT, CHECK
	String constraint_secondary_key; //LESS_THAN, GREATER_THAN, EQUAL_TO, NOT_EQUAL_TO, TABLE_NAME
	String constraint_value; // value or column name
};
*/

class Table {
private:
    String table_name;
    Vector<String> headers;
    Vector<String> data_types;
    Vector<String> constraints; // Store constraints like PRIMARY_KEY, FOREIGN_KEY
    Vector<Vector<Cell>> table_data;
    Vector<int> primary_key_indices; // Indices of primary key columns
    Vector<pair<int, String>> foreign_key_indices; // (column index, referenced table name)

public:

    // Default constructor
    Table() {}

    // Constructor - to be updated to store primary key and foreign key info
    Table(String table_name, Vector<Vector<String>> col_data) {
        this->table_name = table_name;
        extract_col_data(col_data);
    }

    Table(String table_name, Vector<String> headers, Vector<String> data_types, Vector<String> constraints) {
            this->table_name = table_name;
            this->headers = headers;
            this->data_types = data_types;
            this->constraints = constraints;
        }

    // Extract column data and store primary and foreign key information
    void extract_col_data(Vector<Vector<String>> temp_col_data) {
        int num_headers = temp_col_data.get_size();
        for (int i = 0; i < num_headers; ++i) {
            headers.push_back(temp_col_data[i][0]);
            data_types.push_back(temp_col_data[i][1]);
            constraints.push_back(temp_col_data[i][2]);

            // Check for primary key constraint
            if (constraints[i] == String("PRIMARY_KEY")) {
                primary_key_indices.push_back(i);
            }

            // Check for foreign key constraint
            if (constraints[i] == String("FOREIGN_KEY")) {
                foreign_key_indices.push_back({i, temp_col_data[i][3]});  // (index, referenced table name)
            }
        }
    }

    // Getter for table name
    String getTableName() const {
        return table_name;
    }

    // Getter for headers
    Vector<String> getHeaders() const {
        return headers;
    }

    // Getter for data_types
    Vector<String> getDataTypes() const {
        return data_types;
    }

    // Getter for constraints
    Vector<String> getConstraints() const {
        return constraints;
    }

    // Getter for table_data
    Vector<Vector<Cell>> getTableData() const {
        return table_data;
    }

    // Getter for primary key columns
    Vector<int> getPrimaryKeyIndices() const {
        return primary_key_indices;
    }

    // Getter for foreign key columns
    Vector<pair<int, String>> getForeignKeyIndices() const {
        return foreign_key_indices;
    }

    // Method to check if primary key value exists
    bool primaryKeyExists(const Vector<Cell>& row) {
        for (int i = 0; i < primary_key_indices.get_size(); ++i) {
            for (int j = 0; j < table_data.get_size(); ++j) {
                if (table_data[j][primary_key_indices[i]].getString() == row[primary_key_indices[i]].getString()) {
                    return true; // Duplicate primary key found
                }
            }
        }
        return false;
    }

    // Method to check if foreign key value exists in referenced table
    bool foreignKeyExists(int col_index, const String& value) {
        String referenced_table = foreign_key_indices[col_index].second;
        // Retrieve the referenced table and check for matching primary key
        // Assuming 'get_table_by_name' retrieves a table by name (implement as needed)
        Table ref_table = get_table_by_name(referenced_table);
        for (int i = 0; i < ref_table.getTableData().get_size(); ++i) {
            if (ref_table.getTableData()[i][primary_key_indices[0]].getString() == value) {
                return true;
            }
        }
        return false;
    }

    void setHeaders(Vector<String> new_headers) {
        headers = new_headers;
    }

    // Method to update records in the table
    void updateRecords(Vector<Vector<Cell>> cell_data) {
        table_data = cell_data;
    }

    // Method to update a single record
    void updateSingleRecord(Vector<Cell> cell_data) {
        table_data.push_back(cell_data);
    }

    // Helper method to get the referenced table by name
    Table get_table_by_name(const String& name) {
        // You would need to implement a way to get the table by name from the database or from stored tables
        return Table(); // Placeholder implementation
    }
};


// previous one
// class Table {
// private:
//     String table_name;
//     Vector<String> headers;
//     Vector<String> data_types;
//     Vector<String> constraints; // Store constraints like PRIMARY_KEY, FOREIGN_KEY
//     Vector<Vector<Cell>> table_data;
//     Vector<int> primary_key_indices; // Indices of primary key columns
//     Vector<pair<int, String>> foreign_key_indices; // (column index, referenced table name)

// public:
//     // Default constructor
//     Table() {}

//     // Constructor - to be updated to store primary key and foreign key info
//     Table(String table_name, Vector<Vector<String>> col_data) {
//         this->table_name = table_name;
//         extract_col_data(col_data);
//     }

//     void setHeaders(Vector<String> new_headers) {
//         headers = new_headers;
//     }

//     // Extract column data and store primary and foreign key information
//     void extract_col_data(Vector<Vector<String>> temp_col_data) {
//         int num_headers = temp_col_data.get_size();
//         for (int i = 0; i < num_headers; ++i) {
//             headers.push_back(temp_col_data[i][0]);
//             data_types.push_back(temp_col_data[i][1]);
//             constraints.push_back(temp_col_data[i][2]);

//             // Check for primary key constraint
//             if (constraints[i] == String("PRIMARY_KEY")) {
//                 primary_key_indices.push_back(i);
//             }

//             // Check for foreign key constraint
//             if (constraints[i] == String("FOREIGN_KEY")) {
//                 foreign_key_indices.push_back({i, temp_col_data[i][3]});  // (index, referenced table name)
//             }
//         }
//     }


//     // Getter for table name
//     String getTableName() const {
//         return table_name;
//     }

//     // Getter for headers
//     Vector<String> getHeaders() const {
//         return headers;
//     }

//     // Getter for data_types
//     Vector<String> getDataTypes() const {
//         return data_types;
//     }

//     // Getter for constraints
//     Vector<String> getConstraints() const {
//         return constraints;
//     }

//     // Getter for table_data
//     Vector<Vector<Cell>> getTableData() const {
//         return table_data;
//     }

//     // Getter for primary key columns
//     Vector<int> getPrimaryKeyIndices() const {
//         return primary_key_indices;
//     }

//     // Getter for foreign key columns
//     Vector<pair<int, String>> getForeignKeyIndices() const {
//         return foreign_key_indices;
//     }

//     // Method to check if primary key value exists
//     bool primaryKeyExists(const Vector<Cell>& row) {
//         for (int i = 0; i < primary_key_indices.get_size(); ++i) {
//             for (int j = 0; j < table_data.get_size(); ++j) {
//                 if (table_data[j][primary_key_indices[i]].getString() == row[primary_key_indices[i]].getString()) {
//                     return true; // Duplicate primary key found
//                 }
//             }
//         }
//         return false;
//     }

//     // Method to check if foreign key value exists in referenced table
//     bool foreignKeyExists(int col_index, const String& value) {
//         String referenced_table = foreign_key_indices[col_index].second;
//         // Retrieve the referenced table and check for matching primary key
//         // Assuming 'get_table_by_name' retrieves a table by name (implement as needed)
//         Table ref_table = get_table_by_name(referenced_table);
//         for (int i = 0; i < ref_table.getTableData().get_size(); ++i) {
//             if (ref_table.getTableData()[i][primary_key_indices[0]].getString() == value) {
//                 return true;
//             }
//         }
//         return false;
//     }

//     // Method to update records in the table
//     void updateRecords(Vector<Vector<Cell>> cell_data) {
//         table_data = cell_data;
//     }

//     // Method to update a single record
//     void updateSingleRecord(Vector<Cell> cell_data) {
//         table_data.push_back(cell_data);
//     }

//     // Helper method to get the referenced table by name
//     Table get_table_by_name(const String& name) {
//         // You would need to implement a way to get the table by name from the database or from stored tables
//         return Table(); // Placeholder implementation
//     }
// };

#endif

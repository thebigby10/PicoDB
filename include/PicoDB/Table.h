#ifndef TABLE_H // Include guard start
#define TABLE_H
#include<iostream>
#include "String.h"
#include "Vector.h"
#include "Cell.h"

using namespace std;

/*
class Constraints{
public:
	String constraint_key; // NOT_NULL, UNIQUE, PEIMARY_KEY, FOREIGN_KEY, DEFAULT, CHECK
	String constraint_secondary_key; //LESS_THAN, GREATER_THAN, EQUAL_TO, NOT_EQUAL_TO, TABLE_NAME
	String constraint_value; // value or column name
};
*/

class Table{

private:
	String table_name;
	Vector<String> headers;
	Vector<String> data_types;
	Vector<String> constraints;
	Vector<Vector<Cell>> table_data;
    Vector<int> primary_key_indices; // Indices of primary key columns
    Vector<pair<int, String>> foreign_key_indices; // (column index, referenced table name)

	/*
		String constrain_key;
		// NOT_NULL, UNIQUE, PEIMARY_KEY, FOREIGN_KEY, DEFAULT, CHECK
		String constrain_secondary_key;
		//LESS_THAN, GREATER_THAN, EQUAL_TO, NOT_EQUAL_TO, TABLE_NAME
		String constrain_value;
		// value or column name
	*/

public:
    // Default constructor
    Table() : table_name(""), headers(), data_types(), constraints(), table_data() {}

	// new constructor - is used in createTable in picoDB class
	Table(String table_name, Vector<Vector<String>> col_data){
		this->table_name = table_name;
		extract_col_data(col_data);
	}

	//constructor overloader - is used in loadCurrentTables in Database class
	Table(String table_name, Vector<String> headers, Vector<String> data_types, Vector<String> constraints)
	: table_name(table_name), headers(headers), data_types(data_types), constraints(constraints){
	}

	// Getter for foreign key references

    // Getter for the table data
    Vector<Vector<Cell>>& getTableData() {
        return table_data;
    }

    // Implementation of the deleteRows method
    bool deleteRows(Vector<String> condition_columns, Vector<String> condition_values, String cascade_or_setnull) {
        Vector<int> condition_indices;

        // Find the column indices for the conditions
        for (size_t i = 0; i < condition_columns.get_size(); ++i) {
            bool found = false;
            for (size_t j = 0; j < headers.get_size(); ++j) {
                if (headers[j] == condition_columns[i]) {
                    condition_indices.push_back(j);
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cerr << "Column " << condition_columns[i] << " not found in table " << table_name << std::endl;
                return false; // If a column is not found, abort the deletion
            }
        }

        // Vector to hold rows to be deleted
        Vector<int> rows_to_delete;

        // Find the rows that match the condition
        for (int i = 0; i < table_data.get_size(); ++i) {
            bool match = true;
            for (size_t j = 0; j < condition_indices.get_size(); ++j) {
                if (table_data[i][condition_indices[j]].getString() != condition_values[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                rows_to_delete.push_back(i);
            }
        }

        // Now delete the rows
        for (int i = rows_to_delete.get_size() - 1; i >= 0; --i) {
            // If CASCADE is specified, we need to delete rows in other tables that reference this row (foreign key constraints)
            if (cascade_or_setnull == String("CASCADE")) {
                for (size_t fk_idx = 0; fk_idx < foreign_key_indices.get_size(); ++fk_idx) {
                    // Implement cascade logic here
                    // Iterate through other tables and delete the rows referencing this row
                    // This is where foreign key cascade deletion is handled
                }
            }

            // If SET_NULL is specified, we need to set foreign key columns to NULL in other tables
            if (cascade_or_setnull == String("SET_NULL")) {
                for (size_t fk_idx = 0; fk_idx < foreign_key_indices.get_size(); ++fk_idx) {
                    // Implement set_null logic here
                    // Iterate through other tables and set the foreign key to NULL
                    // This is where foreign key set-null operation is handled
                }
            }

            // Finally, delete the row from the table data
            table_data.erase(rows_to_delete[i]);
        }
        return true;
    }

	//update table with new data
    void extract_col_data(Vector<Vector<String>> temp_col_data) {
        int num_headers = temp_col_data.get_size();
        for (int i = 0; i < num_headers; ++i) {
            if (temp_col_data[i].get_size() > 0) {headers.push_back(temp_col_data[i][0]);}
            if (temp_col_data[i].get_size() > 1) {data_types.push_back(temp_col_data[i][1]);}
            if (temp_col_data[i].get_size() > 2) {constraints.push_back(temp_col_data[i][2]);}

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


	// to update table cells
	void updateRecords (Vector<Vector<Cell>> cell_data) {
		this->table_data = cell_data;
	}

	void updateSingleRecord (Vector<Cell> cell_data) {
		this->table_data.push_back(cell_data);
	}

    // Getter for table_name
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

	// set header
	void setHeaders(Vector<String> headers) {
		this->headers = headers;
	}

	// Additional methods for row management
	Vector<String> get_Row() {
		return headers;
	}

	int get_RowSize() {
		return table_data.get_size();
	}

	// Getter for primary key columns
    Vector<int> getPrimaryKeyIndices() const {
        return primary_key_indices;
    }

    // Getter for foreign key columns
    Vector<pair<int, String>> getForeignKeyIndices() const {
        return foreign_key_indices;
    }

    // // Method to check if primary key value exists
    // bool primaryKeyExists(const Vector<Cell>& row) {
    //     for (int i = 0; i < primary_key_indices.get_size(); ++i) {
    //         for (int j = 0; j < table_data.get_size(); ++j) {
    //             if (table_data[j][primary_key_indices[i]].getString() == row[primary_key_indices[i]].getString()) {
    //                 return true; // Duplicate primary key found
    //             }
    //         }
    //     }
    //     return false;
    // }

    // // Method to check if foreign key value exists in referenced table
    // bool foreignKeyExists(int col_index, const String& value) {
    //     String referenced_table = foreign_key_indices[col_index].second;
    //     // Retrieve the referenced table and check for matching primary key
    //     // Assuming 'get_table_by_name' retrieves a table by name (implement as needed)
    //     Table ref_table = get_table_by_name(referenced_table);
    //     for (int i = 0; i < ref_table.getTableData().get_size(); ++i) {
    //         if (ref_table.getTableData()[i][primary_key_indices[0]].getString() == value) {
    //             return true;
    //         }
    //     }
    //     return false;
    // }

	// // Helper method to get the referenced table by name
    // Table get_table_by_name(const String& name) {
    //     // You would need to implement a way to get the table by name from the database or from stored tables
    //     return Table(); // Placeholder implementation
    // }

};

#endif

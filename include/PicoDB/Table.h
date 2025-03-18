#ifndef TABLE_H // Include guard start
#define TABLE_H
#include<iostream>
#include "String.h"
#include "Vector.h"
#include "Cell.h"
#include <map>

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

    // Default constructor for innerJoin result table
    Table(String table_name) : table_name(table_name), headers(), data_types(), constraints(), table_data() {}

	//constructor overloader - is used in loadCurrentTables in Database class
	Table(String table_name, Vector<String> headers, Vector<String> data_types, Vector<String> constraints)
	: table_name(table_name), headers(headers), data_types(data_types), constraints(constraints){
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

	// ✅ Get the index of a column by its name
	int getColumnIndex(const String& colName) const {
        for (int i = 0; i < headers.get_size(); i++) {
            if (headers[i] == colName) {
                return i;
            }
        }
        return -1; // Not found
    }
	// void setHeadersFromVector(const Vector<String>& newHeaders) {
	// 	this->headers = newHeaders;
	// }
	
	// Make sure getTableName() is implemented
	String getTableName() const {
		return table_name;
	}

	// ✅ Get cell value at row i, column j
	 String getCell(int row, int col) const {
        if (row < 0 || row >= table_data.get_size() || col < 0 || col >= table_data[row].get_size()) {
            return ""; // Return empty string if out of bounds
        }
        return table_data[row][col].getString(); // Convert Cell to String
    }

	// ✅ Get number of rows
	int getRowCount() const {
			return table_data.get_size();
	}

    // ✅ Perform an INNER JOIN
	

// ...existing code...

// ...existing code...
Table innerJoin(const Table& rightTable, const String& leftColumn, const String& rightColumn, Vector<String> selectedColumns) {
    int leftColIndex = this->getColumnIndex(leftColumn);
    int rightColIndex = rightTable.getColumnIndex(rightColumn);

    if (leftColIndex == -1 || rightColIndex == -1) {
        std::cerr << "Error: Column not found in one of the tables!" << std::endl;
        return Table(); // Return an empty table
    }

    Table resultTable("InnerJoinResult");
    Vector<Vector<Cell>> resultData;
    Vector<String> resultHeaders;
    std::map<String, bool> seenRows;  // For duplicate row detection

    // Build mapping for selected columns
    Vector<std::pair<String, int>> columnSources;
    for (int k = 0; k < selectedColumns.get_size(); k++) {
        String colName = selectedColumns[k];
        int dotPos = colName.find('.');
        if (dotPos != -1) {
            // Qualified column: e.g., "students.id"
            String tablePrefix = colName.substr(0, dotPos);
            String actualCol = colName.substr(dotPos + 1, colName.length() - dotPos - 1);
            if (tablePrefix == this->getTableName()) {
                int idx = this->getColumnIndex(actualCol);
                if (idx != -1) {
                    columnSources.push_back({"left", idx});
                    resultHeaders.push_back(actualCol);
                } else {
                    std::cerr << "Error: Column '" << actualCol 
                              << "' not found in table " << this->getTableName() << std::endl;
                    return Table();
                }
            } else if (tablePrefix == rightTable.getTableName()) {
                int idx = rightTable.getColumnIndex(actualCol);
                if (idx != -1) {
                    columnSources.push_back({"right", idx});
                    resultHeaders.push_back(actualCol);
                } else {
                    std::cerr << "Error: Column '" << actualCol 
                              << "' not found in table " << rightTable.getTableName() << std::endl;
                    return Table();
                }
            } else {
                std::cerr << "Error: Table prefix '" << tablePrefix 
                          << "' does not match any joined table." << std::endl;
                return Table();
            }
        } else {
            // Unqualified column; check both tables
            int leftIdx = this->getColumnIndex(colName);
            int rightIdx = rightTable.getColumnIndex(colName);
            if (leftIdx != -1) {
                columnSources.push_back({"left", leftIdx});
                resultHeaders.push_back(this->getTableName() + "." + colName);
            } else if (rightIdx != -1) {
                columnSources.push_back({"right", rightIdx});
                resultHeaders.push_back(rightTable.getTableName() + "." + colName);
            } else {
                std::cerr << "Error: Selected column '" << colName 
                          << "' does not exist in either table!" << std::endl;
                return Table();
            }
        }
    }
    resultTable.setHeaders(resultHeaders);

    // Perform the join by comparing trimmed strings.
    for (int i = 0; i < this->getRowCount(); i++) {
        String leftValue = this->table_data[i][leftColIndex].getString().trim();
        for (int j = 0; j < rightTable.getRowCount(); j++) {
            String rightValue = rightTable.table_data[j][rightColIndex].getString().trim();
            if (leftValue == rightValue) {   // Compare the trimmed strings directly
                Vector<Cell> resultRow;
                String rowKey = "";
                for (int k = 0; k < columnSources.get_size(); k++) {
                    String source = columnSources[k].first;
                    int sourceCol = columnSources[k].second;
                    if (source == String("left")) {
                        resultRow.push_back(this->table_data[i][sourceCol]);
                        rowKey += this->table_data[i][sourceCol].getString() + "|";
                    } else { // "right"
                        resultRow.push_back(rightTable.table_data[j][sourceCol]);
                        rowKey += rightTable.table_data[j][sourceCol].getString() + "|";
                    }
                }
                if (seenRows.find(rowKey) == seenRows.end()) {
                    resultData.push_back(resultRow);
                    seenRows.insert({rowKey, true});
                }
            }
        }
    }

    resultTable.updateRecords(resultData);
    return resultTable;
}

// ...existing code...





    // Getter for table_name
	// String getTableName() const {
	// 	return table_name;
	// }

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

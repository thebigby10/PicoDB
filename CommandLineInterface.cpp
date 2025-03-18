#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <filesystem>
#include "include/PicoDB/PicoDB.h"

using namespace std;
namespace fs = std::filesystem;

void printHelp() {
    cout << "\n┌───────────────────────────────────────────────────────────┐\n";
    cout << "│                PicoDB Command Line Interface               │\n";
    cout << "└───────────────────────────────────────────────────────────┘\n\n";
    
    cout << "DATABASE COMMANDS:\n";
    cout << "  create_database <db_name>\n";
    cout << "      Creates a new database with the specified name.\n";
    cout << "      Example: create_database university\n\n";
    
    cout << "  list_databases\n";
    cout << "      Lists all available databases in the system.\n";
    cout << "      Example: list_databases\n\n";
    
    cout << "TABLE COMMANDS:\n";
    cout << "  create_table <table_name> <col1> <type1> <constraint1> [<col2> <type2> <constraint2> ...]\n";
    cout << "      Creates a new table with specified columns.\n";
    cout << "      Supported types: INT, FLOAT, STRING, DATE\n";
    cout << "      Constraints: PRIMARY_KEY, NOT_NULL, UNIQUE, DEFAULT_<value>\n";
    cout << "      Example: create_table students id INT PRIMARY_KEY name STRING NOT_NULL\n\n";
    
    cout << "DATA MANIPULATION COMMANDS:\n";
    cout << "  insert_into <table_name> <col1> <value1> [<col2> <value2> ...]\n";
    cout << "      Inserts a new record into the specified table.\n";
    cout << "      Example: insert_into students id 1 name John\n\n";
    
    cout << "  select <table_name> [<col1> <col2> ...]\n";
    cout << "      Retrieves data from specified table and columns.\n";
    cout << "      If no columns specified, selects all columns.\n";
    cout << "      Example: select students id name\n\n";
    
    cout << "  delete_from <table_name> <condition>\n";
    cout << "      Deletes records from the specified table based on the condition.\n";
    cout << "      Example: delete_from students id = 1\n\n";
    
    cout << "SYSTEM COMMANDS:\n";
    cout << "  save_db\n";
    cout << "      Saves all changes to the current database.\n";
    cout << "      Example: save_db\n\n";
    
    cout << "  help\n";
    cout << "      Displays this help message.\n";
    cout << "      Example: help\n\n";
    
    cout << "  exit\n";
    cout << "      Exits the PicoDB CLI.\n";
    cout << "      Example: exit\n\n";
    
    cout << "NOTES:\n";
    cout << "  - Commands are case sensitive.\n";
    cout << "  - String values with spaces should be enclosed in quotes (not implemented yet).\n";
    cout << "  - Changes are not saved until 'save_db' command is executed.\n\n";
}

// Function to create a database
void createDatabase(const string& db_path, const string& db_name) {
    string full_path = db_path + "/" + db_name;
    if (fs::create_directory(full_path)) {
        cout << "Database '" << db_name << "' created successfully at " << full_path << ".\n";
    } else {
        cerr << "Failed to create database '" << db_name << "'. It may already exist.\n";
    }
}

// Function to create a table
void createTable(PicoDB& db, const vector<string>& tokens) {
    if (tokens.size() < 4 || (tokens.size() - 2) % 3 != 0) {
        cerr << "Invalid syntax for create_table. Use: create_table <table_name> <col1> <type1> <constraint1> <col2> <type2> <constraint2> ...\n";
        return;
    }

    String table_name(tokens[1].c_str());
    Vector<Vector<String>> col_data;

    for (size_t i = 2; i < tokens.size(); i += 3) {
        Vector<String> col_info;
        col_info.push_back(tokens[i].c_str());     // Column name
        col_info.push_back(tokens[i + 1].c_str()); // Column type
        col_info.push_back(tokens[i + 2].c_str()); // Column constraint
        col_data.push_back(col_info);
    }
    cout << "Creating table with name: " << table_name << "\n";
    for (size_t i = 0; i < col_data.get_size(); ++i) {
        const auto& col = col_data[i];
        cout << "Column: " << col[0] << ", Type: " << col[1] << ", Constraint: " << col[2] << "\n";
    }
    if (db.createTable(table_name, col_data)) {
        cout << "Table '" << table_name << "' created successfully.\n";
    } else {
        cerr << "Failed to create table '" << table_name << "'.\n";
    }
}

// Function to insert data into a table
void insertInto(PicoDB& db, const vector<string>& tokens) {
    if (tokens.size() < 4 || (tokens.size() - 2) % 2 != 0) {
        cerr << "Invalid syntax for insert_into. Use: insert_into <table_name> <col1> <value1> <col2> <value2> ...\n";
        return;
    }

    String table_name(tokens[1].c_str());
    Vector<String> col_names, values;

    for (size_t i = 2; i < tokens.size(); i += 2) {
        col_names.push_back(tokens[i].c_str());
        values.push_back(tokens[i + 1].c_str());
    }

    if (db.insertInto(table_name, col_names, values)) {
        cout << "Record inserted successfully into table '" << table_name << "'.\n";
    } else {
        cerr << "Failed to insert record into table '" << table_name << "'.\n";
    }

    // Debug: Print the inserted values
    cout << "Inserted values: ";
    for (size_t i = 0; i < col_names.get_size(); ++i) {
        cout << col_names[i] << " = " << values[i] << ", ";
    }
    cout << endl;

    // Debug: Print the table data after insertion
    Table table = db.getTable(table_name);
    cout << "Table data after insertion:\n";
    db.printTable(table);
}

// Function to select and display data from a table
void selectFromTable(PicoDB& db, const vector<string>& tokens) {
    if (tokens.size() < 2) {
        cerr << "Invalid syntax for select. Use: select <table_name> <col1> <col2> ...\n";
        return;
    }

    String table_name(tokens[1].c_str());
    Vector<String> cols;

    for (size_t i = 2; i < tokens.size(); ++i) {
        cols.push_back(tokens[i].c_str());
    }

    // Debug: Print the table data before selection
    Table table = db.getTable(table_name);
    cout << "Table data before selection:\n";
    db.printTable(table);

    // Table result = db.select(table_name, cols, "");
    // db.printTable(result);

    // Debug: Print the selected columns
    cout << "Selected columns: ";
    for (size_t i = 0; i < cols.get_size(); ++i) {
        cout << cols[i] << ", ";
    }
    cout << endl;

    // Debug: Print the number of rows in the result
    cout << "Number of rows in result: " << table.getRowCount() << endl;
}

// Function to delete data from a table
void deleteFromTable(PicoDB& db, const vector<string>& tokens) {
    if (tokens.size() < 3) {
        cerr << "Invalid syntax for delete_from. Use: delete_from <table_name> <condition>\n";
        return;
    }

    String table_name(tokens[1].c_str());
    String condition;

    for (size_t i = 2; i < tokens.size(); ++i) {
        condition += tokens[i].c_str();
        if (i < tokens.size() - 1) {
            condition += " ";
        }
    }

    if (db.deleteFrom(table_name, condition)) {
        cout << "Records deleted successfully from table '" << table_name << "' where " << condition << ".\n";
    } else {
        cerr << "Failed to delete records from table '" << table_name << "' where " << condition << ".\n";
    }

    // Debug: Print the table data after deletion
    Table table = db.getTable(table_name);
    cout << "Table data after deletion:\n";
    db.printTable(table);
}

// Function to list available databases
void listDatabases(const string& db_path) {
    cout << "Available databases:\n";
    try {
        for (const auto& entry : fs::directory_iterator(db_path)) {
            if (entry.is_directory()) {
                cout << "  " << entry.path().filename().string() << "\n";
            }
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "Error accessing directory: " << e.what() << "\n";
    }
}

int main() {
    // Initialize PicoDB instance
    PicoDB db("studentdb", "/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb", "admin", "admin");

    cout << "Welcome to PicoDB CLI! Type 'help' for a list of commands.\n";

    string input;
    while (true) {
        cout << "PicoDB> ";
        getline(cin, input);
        if (input.empty()) continue;

        istringstream iss(input);
        vector<string> tokens((istream_iterator<string>(iss)), istream_iterator<string>());

        if (tokens.empty()) continue;

        string command = tokens[0];

        if (command == "create_database") {
            if (tokens.size() != 2) {
                cerr << "Invalid syntax for create_database. Use: create_database <db_name>\n";
            } else {
                createDatabase("/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb", tokens[1]);
            }
        } else if (command == "create_table") {
            createTable(db, tokens);
        } else if (command == "insert_into") {
            insertInto(db, tokens);
        } else if (command == "select") {
            selectFromTable(db, tokens);
        } else if (command == "delete_from") {
            deleteFromTable(db, tokens);
        } else if (command == "save_db") {
            db.saveDB();
            cout << "Database saved successfully.\n";
        } else if (command == "list_databases") {
            listDatabases("/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb");
        } else if (command == "help") {
            printHelp();
        } else if (command == "exit") {
            cout << "Exiting PicoDB CLI.\n";
            break;
        } else {
            cerr << "Unknown command. Type 'help' for available commands.\n";
        }
    }

    return 0;
}

// [DUMMY DATA DO NOT DELETE]
// create_table students id INT PRIMARY_KEY name STRING NOT_NULL
// insert_into students id 1 name John
// insert_into students id 2 name Jane
// select students id name
// delete_from students id = 1
// select students id name
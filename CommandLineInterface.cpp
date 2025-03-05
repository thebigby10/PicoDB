#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include "include/PicoDB/PicoDB.h"


using namespace std;

void printHelp() {
    cout << "Available commands:\n";
    cout << "  create_table <table_name> <col1> <type1> <constraint1> <col2> <type2> <constraint2> ...\n";
    cout << "  insert_into <table_name> <col1> <value1> <col2> <value2> ...\n";
    cout << "  select <table_name> <col1> <col2> ...\n";
    cout << "  save_db\n";
    cout << "  help\n";
    cout << "  exit\n";
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

    Table result = db.select(table_name, cols, "");
    db.printTable(result);
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

        if (command == "create_table") {
            createTable(db, tokens);
        } else if (command == "insert_into") {
            insertInto(db, tokens);
        } else if (command == "select") {
            selectFromTable(db, tokens);
        } else if (command == "save_db") {
            db.saveDB();
            cout << "Database saved successfully.\n";
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
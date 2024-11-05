#include <bits/stdc++.h>
#include <iostream>
#include "../include/PicoDB/PicoDB.h"
#include "../src/FileHandler.cpp"
#include "../src/Database.cpp"
#include "../src/Table.cpp" 

void printTable(const Table& table);

using namespace std;

int main() {
    // Create or use existing database
    PicoDB rapidb("rapidb", "/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb", "rapi69", "_key_", ",_,");
    
    // Create a table named "person_info"
    rapidb.createTable(String("person_info"), {
        {"id", "INT", "PRIMARY_KEY", ""},
        {"name", "STRING", "NOT_NULL", ""}
    });

    // Insert data into the "person_info" table
    // Here we can assume you have a method to insert data, such as:
    //rapidb.insert("person_info", {{"1", "Alice"}, {"2", "Bob"}, {"3", "Charlie"}});

    // Select from the "person_info" table
    //Table selectedTable = 
	rapidb.select("person_info", {});

    // Print the selected table
    //

    // Save the database
    rapidb.saveDB();

    return 0; // Return success status
};


#include <bits/stdc++.h>
#include <iostream>
#include <gtest/gtest.h>
#include "../include/PicoDB/PicoDB.h"
#include "../CommandLineInterface.cpp"

TEST(CreateTableTest, BasicAssertions) {
    // Initialize PicoDB instance
    PicoDB db("testdb", "/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb", "admin", "admin");

    // Create Table
    bool result = db.createTable("students", {
        {"id", "INT", "PRIMARY_KEY", ""},
        {"name", "STRING", "NOT_NULL", ""}
    });

    // Check if the table was created successfully
    ASSERT_TRUE(result);

    // Check if the table exists in the database
    Vector<Table>& tables = db.getTables();
    bool table_found = false;
    for (int i = 0; i < tables.get_size(); ++i) {
        if (std::string(tables[i].getTableName()) == "students") {
            table_found = true;
            break;
        }
    }
    ASSERT_TRUE(table_found);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
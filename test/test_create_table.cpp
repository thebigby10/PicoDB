#include <gtest/gtest.h>
#include "../include/PicoDB/PicoDB.h"
#include "../CommandLineInterface.cpp"

TEST(CreateTableTest, ValidTableCreation) {
    // Initialize PicoDB instance
    PicoDB db("testdb", "/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb", "admin", "admin");

    // Define the command tokens for creating a table
    std::vector<std::string> tokens = {"create_table", "students", "id", "INT", "PRIMARY_KEY", "name", "STRING", "NOT_NULL", "age", "INT"};

    // Call the createTable function
    createTable(db, tokens);

    // Verify that the table was created successfully
    Vector<Table>& tables = db.getTables();
    bool tableFound = false;
    for (int i = 0; i < tables.get_size(); ++i) {
        if (std::string(tables[i].getTableName()) == std::string("students")) {
            tableFound = true;
            break;
        }
    }

    // Assert that the table was found
    ASSERT_TRUE(tableFound) << "Table 'students' was not created successfully";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
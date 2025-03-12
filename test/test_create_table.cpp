#include <gtest/gtest.h>
#include "../include/PicoDB/PicoDB.h"


TEST(CreateTableTest, BasicAssertions) {
    // Initialize PicoDB instance
    PicoDB db("testdb", "/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb", "admin", "admin");

  
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

// we need to explicitly mention this for work 
// else , we need to change the path on , add these lines to your ~/.zshrc or ~/.bashrc:

// g++ test_create_table.cpp -o test_create_table \
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -lgtest -lgtest_main -pthread

#include <iostream>
#include "../include/PicoDB/PicoDB.h"
//#include "/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/CommandLineInterface.cpp"

void testCreateTable() {
    PicoDB db("testdb", "/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb", "admin", "admin");

    bool result = db.createTable("students", {
        {"id", "INT", "PRIMARY_KEY", ""},
        {"name", "STRING", "NOT_NULL", ""}
    });

    if (result) {
        std::cout << "testCreateTable passed.\n";
    } else {
        std::cerr << "testCreateTable failed.\n";
    }
}

void testInsertInto() {
    PicoDB db("testdb", "/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb", "admin", "admin");
    db.createTable("students", {
        {"id", "INT", "PRIMARY_KEY", ""},
        {"name", "STRING", "NOT_NULL", ""}
    });

    bool result = db.insertInto("students", {"id", "name"}, {"1", "John Doe"});

    if (result) {
        std::cout << "testInsertInto passed.\n";
    } else {
        std::cerr << "testInsertInto failed.\n";
    }
}

void testSelect() {
    PicoDB db("testdb", "/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb", "admin", "admin");
    db.createTable("students", {
        {"id", "INT", "PRIMARY_KEY", ""},
        {"name", "STRING", "NOT_NULL", ""}
    });
    db.insertInto("students", {"id", "name"}, {"1", "John Doe"});

    Table result = db.select("students", {"id", "name"}, "id = 1");

    if (result.getRowCount() == 1 && std::string(result.getCell(0, 0)) == "1" && std::string(result.getCell(0, 1)) == "John Doe") {
        std::cout << "testSelect passed.\n";
    } else {
        std::cerr << "testSelect failed.\n";
    }
}

void testAlwaysPass() {
    std::cout << "testAlwaysPass passed.\n";
}
void testAlwaysFail() {
    std::cerr << "testAlwaysFail failed.\n";
}
 
void testCLI() {
    // Initialize CommandLineInterface with the test database path
    // implementation
    
}
int main() {
    testCreateTable();
    testInsertInto();
    testSelect();
    testAlwaysPass();
    testAlwaysFail();
    return 0;
}

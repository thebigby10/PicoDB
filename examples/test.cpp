#include <iostream>
using namespace std;
#include "../include/PicoDB/PicoDB.h"

int main() {
    // // Initialize Database
    PicoDB db("studentdb", "/home/thebigby01/Codes/_github_repos/PicoDB/examples", "admin", "1234");

    // Create a table
    db.createTable("students", {
        {"id", "INT"}, {"name", "STRING"}, {"age", "INT"}, {"is_active", "BOOLEAN"}
    });

    // Insert some data
    db.insertInto("students", {"id", "name", "age", "is_active"}, {"1", "John Doe", "20", "true"});
    db.insertInto("students", {"id", "name", "age", "is_active"}, {"2", "Jane Smith", "18", "false"});
    db.insertInto("students", {"id", "name", "age", "is_active"}, {"3", "Alice Brown", "22", "true"});
    db.insertInto("students", {"id", "name", "age", "is_active"}, {"4", "Sakib Khan", "12", "false"});
    db.insertInto("students", {"id", "name", "age", "is_active"}, {"5", "Sakib Al Hasan", "15", "true"});

    // Print full table (no condition)
    Table result1 = db.select("students", {"id", "name", "age", "is_active"}, "age != 18");
    db.printTable(result1);

    // Cell c1(true);
    // cout<<(c1.getDataType()==DataType::BOOLEAN)<<endl;

    return 0;
}

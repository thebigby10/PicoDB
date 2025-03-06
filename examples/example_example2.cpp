#include <iostream>
#include "../include/PicoDB/PicoDB.h"

int main() {
    // Initialize Database
    PicoDB db("studentdb", "/home/thebigby01/Codes/_github_repos/PicoDB/examples", "admin", "1234");

    // Create a table
    db.createTable("students", {
        {"id", "INT"}, {"name", "STRING"}, {"age", "INT"}, {"is_active", "BOOLEAN"}
    });

    // Insert some data
    db.insertInto("students", {"id", "name", "age", "is_active"}, {"1", "John Doe", "20", "true"});
    db.insertInto("students", {"id", "name", "age", "is_active"}, {"2", "Jane Smith", "18", "false"});
    db.insertInto("students", {"id", "name", "age", "is_active"}, {"3", "Alice Brown", "12", "true"});

    // Print full table (no condition)
    std::cout << "🔹 SELECT * FROM students;" << std::endl;
    Table result1 = db.select("students", {"id", "name", "age", "is_active"}, "");
    db.printTable(result1);

    // Select with condition: age > 18
    std::cout << "\n🔹 SELECT id, name FROM students WHERE age < 18;" << std::endl;
    Table result2 = db.select("students", {"id", "name"}, "age < 18");
    db.printTable(result2);

    // Select with AND condition
    std::cout << "\n🔹 SELECT name, age FROM students WHERE age > 18 AND is_active = true;" << std::endl;
    Table result3 = db.select("students", {"name", "age"}, "age > 18 AND is_active = true");
    db.printTable(result3);

    // Select with OR condition
    std::cout << "\n🔹 SELECT id, name FROM students WHERE name = \"Jane Smith\" OR age < 20;" << std::endl;
    Table result4 = db.select("students", {"id", "name"}, "name = \"Jane Smith\" OR age < 20");
    db.printTable(result4);

    return 0;
}

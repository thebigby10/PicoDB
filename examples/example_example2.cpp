#include <iostream>
#include "../include/PicoDB/PicoDB.h"

int main() {
    // Initialize Database
    PicoDB zawadDB("zawadDB", "../test/zawadDB", "admin", "1234", ",");

    // Create a table
    zawadDB.createTable("students", {
        {"id", "INT"}, {"name", "STRING"}, {"age", "INT"}, {"is_active", "BOOLEAN"}
    });

    // Insert some data
    zawadDB.insertInto("students", {"id", "name", "age", "is_active"}, {"1", "John Doe", "20", "true"});
    zawadDB.insertInto("students", {"id", "name", "age", "is_active"}, {"2", "Jane Smith", "18", "false"});
    zawadDB.insertInto("students", {"id", "name", "age", "is_active"}, {"3", "Alice Brown", "22", "true"});

    // Print full table (no condition)
    std::cout << "🔹 SELECT * FROM students;" << std::endl;
    Table result1 = zawadDB.select("students", {"id", "name", "age", "is_active"}, "");
    zawadDB.printTable(result1);

    // Select with condition: age > 18
    std::cout << "\n🔹 SELECT id, name FROM students WHERE age > 18;" << std::endl;
    Table result2 = zawadDB.select("students", {"id", "name"}, "age > 18");
    zawadDB.printTable(result2);

    // Select with AND condition
    std::cout << "\n🔹 SELECT name, age FROM students WHERE age > 18 AND is_active = true;" << std::endl;
    Table result3 = zawadDB.select("students", {"name", "age"}, "age > 18 AND is_active = true");
    zawadDB.printTable(result3);

    // Select with OR condition
    std::cout << "\n🔹 SELECT id, name FROM students WHERE name = \"Jane Smith\" OR age < 20;" << std::endl;
    Table result4 = zawadDB.select("students", {"id", "name"}, "name = \"Jane Smith\" OR age < 20");
    zawadDB.printTable(result4);

    return 0;
}

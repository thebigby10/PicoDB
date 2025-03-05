#include "../include/PicoDB/PicoDB.h"

int main(){
    // Initialize PicoDB instance
        PicoDB zawadDB("zawadDB", "D:/SPL Projects/PicoDB/test/zawadDB", "admin", "admin", ",");

        // Create Table
        zawadDB.createTable("students", {
            {"id", "INT"},
            {"name", "STRING"},
            {"age", "INT"},
            {"is_active", "BOOLEAN"}
        });

        // Insert sample data
        zawadDB.insertInto("students", {"id", "name", "age", "is_active"}, {"1", "John", "20", "true"});
        zawadDB.insertInto("students", {"id", "name", "age", "is_active"}, {"2", "Alice", "17", "true"});
        // testdb.insertInto(String table_name, Vector<String> col_names, Vector<String> values)

        // Select records where age > 18 and name is NOT "Alice"
        //Table result = zawadDB.select("students", {"id", "name", "age"}, "age > 18");
        zawadDB.select("students", {"id", "name", "age"}, "age > 18");

        // Display the result
        // zawadDB.printTable(result);

        // testdb.saveDB();


        return 0;

}
#include "../include/PicoDB/PicoDB.h"

int main(){
    // Initialize PicoDB instance
        PicoDB testdb("studentdb", "/home/thebigby01/Codes/_github_repos/PicoDB/examples", "admin", "admin");

        // Create Table
        testdb.createTable("students", {
            {"id", "INT"},
            {"name", "STRING"},
            {"age", "INT"},
            {"is_active", "BOOLEAN"}
        });

        // Insert sample data
        testdb.insertInto("students", {"id", "name", "age", "is_active"}, {"1", "John", "20", "true"});
        testdb.insertInto("students", {"id", "name", "age", "is_active"}, {"2", "Alice", "18", "true"});
        // testdb.insertInto(String table_name, Vector<String> col_names, Vector<String> values)

        // Select records where age > 18 and name is NOT "Alice"
        Table result = testdb.select("students", {"id", "name", "age"}, "age = 18");

        // Display the result
        testdb.printTable(result);

        // testdb.saveDB();


        return 0;

}

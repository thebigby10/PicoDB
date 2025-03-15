#include <iostream>
#include "../include/PicoDB/PicoDB.h"

int main() {
    // Initialize Database
    PicoDB zawadDB("zawadDB", "examples/testdb/zawadDB", "rapi", "5", ",");

    // Create a table
    zawadDB.createTable("students", {
        {"id", "INT", "PRIMARY_KEY"}, {"name", "STRING", "NOT_NULL"}, {"age", "INT", "NOT_NULL"}, {"is_active", "BOOLEAN", "DEFAULT"}
    });

    // create a new table named courses
    zawadDB.createTable("courses", {
        {"course_id", "INT", "PRIMARY_KEY"}, {"course_name", "STRING", "NOT_NULL"}, {"student_id", "INT", "FOREIGN_KEY REFERENCES students(id)"}
    });

    // // Insert some data
    zawadDB.insertInto("students", {"id", "name", "age", "is_active"}, {"1", "John Doe", "20", "true"});
    zawadDB.insertInto("students", {"id", "name", "age", "is_active"}, {"2", "Jane Smith", "18", "false"});
    zawadDB.insertInto("students", {"id", "name", "age", "is_active"}, {"3", "Alice Brown", "15", "true"});

    // insert into courses
    zawadDB.insertInto("courses", {"course_id", "course_name", "student_id"}, {"1", "Math", "1"});
    zawadDB.insertInto("courses", {"course_id", "course_name", "student_id"}, {"2", "Science", "2"});
    zawadDB.insertInto("courses", {"course_id", "course_name", "student_id"}, {"3", "English", "3"});
    zawadDB.insertInto("courses", {"course_id", "course_name", "student_id"}, {"4", "History", "1"});
    zawadDB.insertInto("courses", {"course_id", "course_name", "student_id"}, {"5", "Geography", "2"});


    // inner join portion
    std::cout << "🔹 Performing INNER JOIN between students and courses..." << std::endl;
    Table result = zawadDB.innerJoin(
        "students",    // Left table
        "courses",     // Right table
        "students.id", // Left table column
        "courses.student_id", // Right table column
        {"students.id", "students.name", "courses.course_name"} // Selected columns
    );

    // Print the result of INNER JOIN
    std::cout << "\n🔹 SELECT students.id, students.name, courses.course_name FROM students "
                 "INNER JOIN courses ON students.id = courses.student_id;\n" << std::endl;
    zawadDB.printTable(result);



    // Print full table (no condition)
    std::cout << "🔹 SELECT * FROM students;" << std::endl;
    Table result1 = zawadDB.select("students", {"id", "name"}, "");
  // zawadDB.printTable(result1);

    // print the courses table
    std::cout << "🔹 SELECT * FROM courses;" << std::endl;
    Table result2 = zawadDB.select("courses", {"course_id", "course_name", "student_id"}, "");
   // zawadDB.printTable(result2);


    // inner join 
   // std::cout << "🔹 SELECT * FROM students INNER JOIN courses ON students.id = courses.student_id;" << std::endl;

    // // Create a table BY NON ADMIN USER
    // zawadDB.createTable("department", {
    //     {"id", "INT", "PRIMARY_KEY"}, {"name", "STRING", "NOT_NULL"}
    // });

    // // Insert some data in new table by NON ADMIN USER
    // zawadDB.insertInto("department", {"id", "name"}, {"1", "Mechanical"});
    // zawadDB.insertInto("department", {"id", "name"}, {"2", "Computer Science"});
    // zawadDB.insertInto("department", {"id", "name"}, {"3", "Electrical"});



    // // Select with condition: age > 18
    // std::cout << "\n🔹 SELECT id, name FROM students WHERE age > 18;" << std::endl;
    // Table result2 = zawadDB.select("students", {"id", "name"}, "age > 18");
    // zawadDB.printTable(result2);

    // // Select with AND condition
    // std::cout << "\n🔹 SELECT name, age FROM students WHERE age > 18 AND is_active = true;" << std::endl;
    // Table result3 = zawadDB.select("students", {"name", "age"}, "age > 18 AND is_active = true");
    // zawadDB.printTable(result3);

    // // Select with OR condition
    // std::cout << "\n🔹 SELECT id, name FROM students WHERE name = \"Jane Smith\" OR age < 20;" << std::endl;
    // Table result4 = zawadDB.select("students", {"id", "name"}, "name = \"Jane Smith\" OR age < 20");
    // zawadDB.printTable(result4);


    //------------------------------------------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------------------------------------
    // Create a table for UserPermission demo
    // zawadDB.createTable("teachers", {
    //     {"id", "INT", "PRIMARY_KEY"}, {"name", "STRING", "NOT_NULL"}, {"salary", "INT", "NOT_NULL"}, {"is_employed", "BOOLEAN", "DEFAULT"}
    // });

    // // Insert some data
    // zawadDB.insertInto("teachers", {"id", "name", "salary", "is_employed"}, {"1", "John Doe", "2000", "true"});
    // zawadDB.insertInto("teachers", {"id", "name", "salary", "is_employed"}, {"2", "Jane Smith", "1800", "false"});
    // zawadDB.insertInto("teachers", {"id", "name", "salary", "is_employed"}, {"3", "Alice Brown", "1500", "true"});

    // // // // User permissions
	// zawadDB.addUser("utsho", "students");
    // std::cout << "\n🔹 Added new user named utsho with permissions on students" << std::endl;
	// zawadDB.addUser("rapi", "teachers");
    // std::cout << "\n🔹 Add new user named rapi with permissions on teachers" << std::endl;
	// zawadDB.grantPermission("utsho", "teachers");
    // std::cout << "\n🔹 Granted access permissions on teachers to user utsho " << std::endl;
	// zawadDB.revokePermission("utsho", "teachers");

    zawadDB.saveDB();

    return 0;
}

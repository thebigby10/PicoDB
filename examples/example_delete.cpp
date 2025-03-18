#include <iostream>
#include "../include/PicoDB/PicoDB.h"

using namespace std;

int main() {
    // Create a database
    PicoDB db("zawadDB", "D:/SPL Projects/PicoDB/test/zawadDB", "admin", "5", ";_;");

    // // Create a table for courses (primary key on `course_id`)
    // cout << "SQL Query: CREATE TABLE courses (course_id INT PRIMARY_KEY, course_name STRING NOT_NULL);" << endl;
    // db.createTable("courses", {
    //     {"course_id", "INT", "PRIMARY_KEY"},
    //     {"course_name", "STRING", "NOT_NULL"}
    // });

    // // Create a table for students (primary key on `student_id` and foreign key on `course_id` referencing `courses.course_id`)
    // cout << "SQL Query: CREATE TABLE students (student_id INT PRIMARY_KEY, student_name STRING NOT_NULL, course_id INT FOREIGN_KEY REFERENCES courses(course_id));" << endl;
    // db.createTable("students", {
    //     {"student_id", "INT", "PRIMARY_KEY"},
    //     {"student_name", "STRING", "NOT_NULL"},
    //     {"course_id", "INT", "FOREIGN_KEY", "courses", "CASCADE"}  // Foreign key referencing `courses.course_id`
    // });

    // // Create a table for teachers (primary key on `teacher_id`)
    // cout << "SQL Query: CREATE TABLE teachers (teacher_id INT PRIMARY_KEY, salaray INT NOT_NULL,  student_id INT FOREIGN_KEY references students SET_NULL);" << endl;
    // db.createTable("teachers", {
    //     {"teacher_id", "INT", "PRIMARY_KEY"},
    //     {"salary", "INT", "NOT_NULL"},
    //     {"student_id", "INT", "FOREIGN_KEY", "students", "SET_NULL"},
    // });



    // // Insert data into `courses` table
    // cout << "SQL Query: INSERT INTO courses (course_id, course_name) VALUES (101, 'Mathematics');" << endl;
    // db.insertInto("courses", {"course_id", "course_name"}, {"101", "Mathematics"});

    // cout << "SQL Query: INSERT INTO courses (course_id, course_name) VALUES (102, 'Physics');" << endl;
    // db.insertInto("courses", {"course_id", "course_name"}, {"102", "Physics"});

    // // Insert data into `students` table (valid course_id)
    // cout << "SQL Query: INSERT INTO students (student_id, student_name, course_id) VALUES (1, 'John Doe', 101);" << endl;
    // db.insertInto("students", {"student_id", "student_name", "course_id"}, {"1", "John Doe", "101"});

    // cout << "SQL Query: INSERT INTO students (student_id, student_name, course_id) VALUES (2, 'Jane Smith', 102);" << endl;
    // db.insertInto("students", {"student_id", "student_name", "course_id"}, {"2", "Jane Smith", "102"});

    // // Insert data into `teachers` table (valid course_id)
    // cout << "SQL Query: INSERT INTO teachers (teacher_id, salary, student_id) VALUES (1, '20000', 1);" << endl;
    // db.insertInto("teachers", {"teacher_id", "salary", "student_id"}, {"1", "20000", "1"});

    // cout << "SQL Query: INSERT INTO teachers (teacher_id, salary, student_id) VALUES (2, '50000', 2);" << endl;
    // db.insertInto("teachers", {"teacher_id", "salary", "student_id"}, {"2", "50000", "2"});


    // // example deleteFROM() with ON DELETE = CASCADE
    // db.deleteFrom("students", "course_id = 102");

    // example deleteFROM() with ON DELETE = SET_NULL
    // db.deleteFrom("students", "course_id = 102");


    // Step 4: Display the tables after modification
    // cout << "SQL Query: SELECT * FROM courses;" << endl;
    Table courses_table = db.select("courses", {"course_id", "course_name"}, "");
    db.printTable(courses_table);

    // cout << "SQL Query: SELECT * FROM students;" << endl;
    Table students_table = db.select("students", {"student_id", "student_name", "course_id"}, "");
    db.printTable(students_table);

    // cout << "SQL Query: SELECT * FROM teachers;" << endl;
    Table teachers_table = db.select("teachers", {"teacher_id", "salary", "student_id"}, "");
    db.printTable(teachers_table);

    // Save the database after operations
    cout << "SQL Query: SAVE DATABASE;" << endl;
    db.saveDB();

    return 0;
}

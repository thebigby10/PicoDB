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
    //     {"student_id", "INT", "FOREIGN_KEY", "students", "CASCADE"},
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

    // cout << "SQL Query: INSERT INTO teachers (teacher_id, salary, student_id) VALUES (2, 'Golam Chishti', 2);" << endl;
    // db.insertInto("teachers", {"teacher_id", "salary", "student_id"}, {"2", "50000", "2"});


    // Incorrect Insert (non-existent course_id)
    // cout << "SQL Query: INSERT INTO students (student_id, student_name, course_id) VALUES (3, 'Alice Brown', 999);" << endl;
    // bool result = db.insertInto("students", {"student_id", "student_name", "course_id"}, {"3", "Alice Brown", "999"});
    // if (!result) {
    //     cout << "Error: Foreign key constraint failed for student Alice Brown!" << endl;
    // }

    // // Insert duplicate primary key (should trigger an error)
    // cout << "SQL Query: INSERT INTO students (student_id, student_name, course_id) VALUES (1, 'Charlie Brown', 101);" << endl;
    // result = db.insertInto("students", {"student_id", "student_name", "course_id"}, {"1", "Charlie Brown", "101"});
    // if (!result) {
    //     cout << "Error: Primary key constraint failed for student ID 1!" << endl;
    // }

    // incorrect update [foreign key breach/parent integrity violation]
    // cout << "SQL Query: UPDATE students SET course_id=103 WHERE student_id=2;" << endl;
    // bool result = db.update("students", {{"course_id", "103"}}, "student_id = 2");
    // if (!result) {
    //     cout << "Error: Foreign key constraint failed for student Jane Smmith" << endl;
    // }


    // correct update
    // cout << "SQL Query: UPDATE students SET course_id=101 WHERE student_id=2;" << endl;
    // bool result = db.update("students", {{"course_id", "101"}}, "student_id = 2");
    // if (!result) {
    //     cout << "Error: Foreign key constraint failed for student Jane Smith!" << endl;
    // }

    // correct update [primary key breach/child integrity violation]
    // cout << "SQL Query: UPDATE courses SET course_id=103 WHERE course_id=101;" << endl;
    // bool result = db.update("courses", {{"course_id", "103"}}, "course_id = 101");
    // if (!result) {
    //     cout << "Error: Foreign key constraint failed for student Jane Smmith" << endl;
    // }

    // correct update [double breach testing]
    cout << "SQL Query: UPDATE students SET student_id=3, course_id=102 WHERE course_id=101;" << endl;
    bool result = db.update("students", {{"student_id", "3"}, {"course_id", "102"}}, "course_id = 101");
    if (!result) {
        cout << "Error: Foreign key constraint failed for student Jane Smmith" << endl;
    }

    // correct update [double breach testing but with on_delete = "SET_NULL"]
    // cout << "SQL Query: UPDATE students SET student_id=3, course_id=102 WHERE course_id=101;" << endl;
    // bool result = db.update("students", {{"student_id", "3"}, {"course_id", "102"}}, "course_id = 101");
    // if (!result) {
    //     cout << "Error: Foreign key constraint failed for student Jane Smmith" << endl;
    // }


    // Step 4: Display the tables after insertion
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

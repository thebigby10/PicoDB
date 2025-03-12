#include <iostream>
#include <vector>
#include "../include/PicoDB/PicoDB.h"

using namespace std;

int main() {
    // Step 1: Create a database and tables with primary key and foreign key constraints
    PicoDB db("schoolDB", "/path/to/db", "admin", "password", ";_;");

    // Create `courses` table (Primary key on `course_id`)
    cout << "SQL Query: CREATE TABLE courses (course_id INT PRIMARY_KEY, course_name STRING NOT_NULL);" << endl;
    db.createTable("courses", {
        {"course_id", "INT", "PRIMARY_KEY"},
        {"course_name", "STRING", "NOT_NULL"},
    });

    // Create `students` table (Primary key on `student_id` and Foreign key on `course_id` referencing `courses.course_id`)
    cout << "SQL Query: CREATE TABLE students (student_id INT PRIMARY_KEY, student_name STRING NOT_NULL, course_id INT FOREIGN_KEY REFERENCES courses(course_id));" << endl;
    db.createTable("students", {
        {"student_id", "INT", "PRIMARY_KEY"},
        {"student_name", "STRING", "NOT_NULL"},
        {"course_id", "INT", "FOREIGN_KEY", "courses"}  // foreign key referencing `courses.course_id`
    });

    // Step 2: Insert data into `courses` table
    cout << "SQL Query: INSERT INTO courses (course_id, course_name) VALUES (101, 'Mathematics');" << endl;
    db.insertInto("courses", {"course_id", "course_name"}, {"101", "Mathematics"});

    cout << "SQL Query: INSERT INTO courses (course_id, course_name) VALUES (102, 'Physics');" << endl;
    db.insertInto("courses", {"course_id", "course_name"}, {"102", "Physics"});

    // Step 3: Insert data into `students` table (ensuring course_id is valid and student_id is unique)
    cout << "SQL Query: INSERT INTO students (student_id, student_name, course_id) VALUES (1, 'John Doe', 101);" << endl;
    db.insertInto("students", {"student_id", "student_name", "course_id"}, {"1", "John Doe", "101"});

    cout << "SQL Query: INSERT INTO students (student_id, student_name, course_id) VALUES (2, 'Jane Smith', 102);" << endl;
    db.insertInto("students", {"student_id", "student_name", "course_id"}, {"2", "Jane Smith", "102"});

    // Incorrect Insert (course_id 999 does not exist in `courses`, should trigger an error)
    cout << "SQL Query: INSERT INTO students (student_id, student_name, course_id) VALUES (3, 'Alice Brown', 999);" << endl;
    bool result = db.insertInto("students", {"student_id", "student_name", "course_id"}, {"3", "Alice Brown", "999"});
    if (!result) {
        cout << "Error: Foreign key constraint failed for student Alice Brown!" << endl;
    }

    // Insert duplicate primary key (should trigger an error)
    cout << "SQL Query: INSERT INTO students (student_id, student_name, course_id) VALUES (1, 'Charlie Brown', 101);" << endl;
    result = db.insertInto("students", {"student_id", "student_name", "course_id"}, {"1", "Charlie Brown", "101"});
    if (!result) {
        cout << "Error: Primary key constraint failed for student ID 1!" << endl;
    }

    // Step 4: Display the tables after insertion
    cout << "SQL Query: SELECT * FROM courses;" << endl;
    Table courses_table = db.select("courses", {"course_id", "course_name"}, "");
    db.printTable(courses_table);

    cout << "SQL Query: SELECT * FROM students;" << endl;
    Table students_table = db.select("students", {"student_id", "student_name", "course_id"}, "");
    db.printTable(students_table);

    // Save the database after operations
    cout << "SQL Query: SAVE DATABASE;" << endl;
    db.saveDB();

    return 0;
}

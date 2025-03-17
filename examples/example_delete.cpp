#include <iostream>
#include "../include/PicoDB/PicoDB.h"

using namespace std;

int main() {
    // Initialize database
    PicoDB db("schoolDB", "/home/thebigby01/Codes/_github_repos/PicoDB/examples/schooldb", "admin", "password", ",_,");

    // Create the students table
    db.createTable("students", {
        {"student_id", "INT", "PRIMARY_KEY"},
        {"student_name", "STRING", "NOT_NULL"},
        {"cgpa", "DOUBLE", "DEFAULT"}
    });

    // Create the courses table with a foreign key reference to students
    db.createTable("courses", {
        {"course_id", "INT", "PRIMARY_KEY"},
        {"course_name", "STRING", "NOT_NULL"},
        {"student_id", "INT", "FOREIGN_KEY", "students"}  // Foreign key reference to students
    });

    // Insert sample data into the students table
    db.insertInto("students", {"student_id", "student_name", "cgpa"}, {"1", "Alice", "3.8"});
    db.insertInto("students", {"student_id", "student_name", "cgpa"}, {"2", "Bob", "2.5"});
    db.insertInto("students", {"student_id", "student_name", "cgpa"}, {"3", "Charlie", "3.2"});

    // Insert sample data into the courses table
    db.insertInto("courses", {"course_id", "course_name", "student_id"}, {"101", "Mathematics", "1"});
    db.insertInto("courses", {"course_id", "course_name", "student_id"}, {"102", "Physics", "2"});
    db.insertInto("courses", {"course_id", "course_name", "student_id"}, {"103", "Chemistry", "3"});

    // Print tables before delete operation
    cout << "Before DELETE operation:" << endl;
    cout << "Students Table:" << endl;
    db.select("students", {});
    cout << "Courses Table:" << endl;
    db.select("courses", {});

    // Perform DELETE operation with CASCADE (this will delete related courses)
    cout << "\nDeleting students with CGPA < 3.5 (CASCADE)..." << endl;
    db.deleteFrom("students", "cgpa < 3.5", "CASCADE");

    // Print tables after CASCADE delete operation
    cout << "\nAfter DELETE operation with CASCADE:" << endl;
    cout << "Students Table:" << endl;
    db.select("students", {"student_id", "student_name"});
    cout << "Courses Table:" << endl;
    db.select("courses", {});

    // Insert students and courses data again for testing SET_NULL
    db.insertInto("students", {"student_id", "student_name", "cgpa"}, {"1", "Alice", "3.8"});
    db.insertInto("students", {"student_id", "student_name", "cgpa"}, {"2", "Bob", "2.5"});
    db.insertInto("students", {"student_id", "student_name", "cgpa"}, {"3", "Charlie", "3.2"});

    db.insertInto("courses", {"course_id", "course_name", "student_id"}, {"101", "Mathematics", "1"});
    db.insertInto("courses", {"course_id", "course_name", "student_id"}, {"102", "Physics", "2"});
    db.insertInto("courses", {"course_id", "course_name", "student_id"}, {"103", "Chemistry", "3"});

    // Perform DELETE operation with SET_NULL (this will set student_id to NULL in courses)
    cout << "\nDeleting students with CGPA < 3.5 (SET_NULL)..." << endl;
    db.deleteFrom("students", "cgpa < 3.5", "SET_NULL");

    // Print tables after SET_NULL delete operation
    cout << "\nAfter DELETE operation with SET_NULL:" << endl;
    cout << "Students Table:" << endl;
    db.select("students", {});
    cout << "Courses Table:" << endl;
    db.select("courses", {});

    return 0;
}

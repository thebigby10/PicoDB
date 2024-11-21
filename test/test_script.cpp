//#include<bits/stdc++.h> //doesnt work on mac hehe
#include<iostream>
#include "../include/PicoDB/PicoDB.h"
#include "../src/Database.cpp"
#include "../src/String.cpp"
#include "../src/Encryptor.cpp"

using namespace std;

int main(){
	PicoDB testDB("testdb", "D:/SPL Projects/PicoDB/test/testDB", "zawad", "5", ",");

	testDB.createTable(String("students"), {
		{"student_id", "INT", "PRIMARY_KEY"},
		{"student_name", "STRING", "NOT_NULL"},
		{"cgpa", "INT","DEFAULT"},
	});

	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042152", "Asif", "4"});
	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042153", "Utsho", "0"});
	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042152", "Mir", "3"});
	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042153", "Zubayer", "3"});
	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042152", "Labonno", "3"});
	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042153", "Charlie", "4"});

    testDB.select("students", {});
	testDB.saveDB();

	// // insert data
	// studentdb.insertInto("student", {"student_id", "student_name", "cgpa"}, {"220042152", "Asif", 0});
	// studentdb.insertInto("student", {"student_id", "student_name", "cgpa"}, {"220042153", "Uthuth", 4});

	// // select data
	// studentdb.select("student", {})
	// studentdb.select("student", {"student_id", "cgpa"});
	// studentdb.selectWhere("student", {}, "cgpa>3.5");
	// studentdb.selectWhere("student", {}, "name LIKE 'A___'";

	// // update data
	// studentdb.update("student", {{"cgpa", "3.9"}}, "student_id=220042152");

	// // delete data
	// studentdb.deleteFrom("student", "cgpa<2.0");
	// studentdb.deleteFrom("student", "name='Asif'");

	// //alter table
    // studentdb.alterTable("student", "ADD", {"email", "STRING"});
    // studentdb.alterTable("student", "DROP", "email");
    // studentdb.alterTable("student", "RENAME_COLUMN", "cgpa", "CGPA");
    // studentdb.alterTable("student", "MODIFY", "cgpa", "FLOAT");
    // studentdb.alterTable("student", "RENAME_TABLE", "studentinfo");

    // //drop table
	// studentdb.dropTable("student", true); // true for cascade



// }

 	//string db_name = "test_db";
    //string db_path = "."; // Current directory

    //Database db(db_name, db_path);

    return 0;

}

//let's have a look on the syntax (rafi - dev)
//Database anotherDB("booksDB", "path/to/db");

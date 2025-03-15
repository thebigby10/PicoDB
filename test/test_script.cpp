//#include<bits/stdc++.h> //doesnt work on mac hehe
#include<iostream>
#include "../include/PicoDB/PicoDB.h"
// #include "../include/PicoDB/Database.h"
// #include "../include/PicoDB/String.h"
// #include "../include/PicoDB/Encryptor.h"

using namespace std;

int main(){
	PicoDB zawadDB("zawadDB", "D:/SPL Projects/PicoDB/test/zawadDB", "utsho", "5", ",");

	zawadDB.createTable(String("students"), {
		{"student_id", "INT", "PRIMARY_KEY"},
		{"student_name", "STRING", "NOT_NULL"},
		{"cgpa", "INT","DEFAULT"},
	});

	zawadDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042150", "Asif", "4"});
	zawadDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042151", "Utsho", "0"});
	zawadDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042152", "Mir", "2"});
	zawadDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042153", "Zubayer", "3"});
	zawadDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042154", "Labonno", "2"});
	zawadDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042155", "Charlie", "4"});

	zawadDB.createTable(String("teachers"), {
		{"teacher_id", "INT", "PRIMARY_KEY"},
		{"teacher_name", "STRING", "NOT_NULL"},
		{"salary", "INT","DEFAULT"},
	});

	zawadDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2134", "Mir Mashkur", "40000"});
	zawadDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2135", "Abu Zobayda", "30000"});
	zawadDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2136", "Lalon Fakir", "45000"});
	zawadDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2137", "Farhad Shikder", "35000"});
	zawadDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2138", "Animesh Ray", "25000"});
	zawadDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2139", "Birbhum Chowdhury", "55000"});


	// // User permissions
	zawadDB.addUser("utsho", "students");
	zawadDB.addUser("rapi", "teachers");
	zawadDB.grantPermission("utsho", "students");
	//testDB.revokePermission("utsho", "teachers");

    zawadDB.select("teachers", {}, "cgpa > 2");
	//testDB.grantPermission("utsho", "teachers");
	//cout << "has reached the end of the programm" << endl;
	zawadDB.saveDB();
	// // insert data
	// studentdb.insertInto("student", {"student_id", "student_name", "cgpa"}, {"220042152", "Asif", 0});
	// studentdb.insertInto("student", {"student_id", "student_name", "cgpa"}, {"220042153", "Uthuth", 4});

	// // select data
	// studentdb.select("student", {})
	// studentdb.select("student", {"student_id", "cgpa"});
	// studentdb.selectWhere("student", {}, "cgpa>3.5");
	// studentdb.selectWhere("student", {}, "name LIKE 'A___'";

	// // update data
	//testdb.update("students", {"cgpa", "3.9"}, {"student_id","=","220042152"});

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

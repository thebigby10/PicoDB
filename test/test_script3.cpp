//#include<bits/stdc++.h> //doesnt work on mac hehe
//#include<iostream>
//#include "../include/PicoDB/PicoDB.h"
#include "D:\SPL Projects\PicoDB\include\PicoDB\PicoDB.h"
// #include "../include/PicoDB/Database.h"
// #include "../include/PicoDB/String.h"
// #include "../include/PicoDB/Encryptor.h"

using namespace std;

int main(){
	PicoDB testDB("testdb", "D:/SPL Projects/PicoDB/test/testDB", "utsho", "5", ",");

	testDB.createTable(String("students"), {
		{"student_id", "INT", "PRIMARY_KEY"},
		{"student_name", "STRING", "NOT_NULL"},
		{"cgpa", "INT","DEFAULT"},
	});

	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042150", "Asif", "4"});
	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042151", "Utsho", "0"});
	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042152", "Mir", "3"});
	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042153", "Zubayer", "3"});
	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042154", "Labonno", "3"});
	testDB.insertInto("students", {"student_id", "student_name", "cgpa"}, {"220042155", "Charlie", "4"});

	testDB.createTable(String("teachers"), {
		{"teacher_id", "INT", "PRIMARY_KEY"},
		{"teacher_name", "STRING", "NOT_NULL"},
		{"salary", "INT","DEFAULT"},
	});

	testDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2134", "Mir Mashkur", "40000"});
	testDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2135", "Abu Zobayda", "30000"});
	testDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2136", "Lalon Fakir", "45000"});
	testDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2137", "Farhad Shikder", "35000"});
	testDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2138", "Animesh Ray", "25000"});
	testDB.insertInto("teachers", {"teacher_id", "teacher_name", "salary"}, {"2139", "Birbhum Chowdhury", "55000"});


	// // User permissions
	testDB.addUser("utsho", "students");
	testDB.addUser("rapi", "teachers");
	testDB.grantPermission("utsho", "students");
	//testDB.revokePermission("utsho", "teachers");

    testDB.select("teachers", {});
	//testDB.grantPermission("utsho", "teachers");
	//cout << "has reached the end of the programm" << endl;
	testDB.saveDB();
    return 0;

}

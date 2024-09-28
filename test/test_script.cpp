#include<bits/stdc++.h>
#include "../include/PicoDB/PicoDB.h"

int main(){
	PicoDB studentdb("studentdb", "/home/thebigby01/tempdb/");
	studentdb.createTable("student", {
		{"student_id", "INT", "PRIMARY_KEY"},
		{"student_name", "STRING", "NOT_NULL"},
		{"cgpa", "INT","DEFAULT 0"},
	});
	
	studentdb.insertData("student", {"student_id", "student_name", "cgpa"}, {"220042152", "Asif", 0});
	studentdb.insertData("student", {"student_id", "student_name", "cgpa"}, {"220042153", "Uthuth", 4});

	studentdb.selectData("student", {})
	studentdb.selectData("student", {"student_id", "cgpa"});
	studentdb.selectDataWhere("student", {}, "cgpa>3");

    studentdb.alterTable("student", "ADD", {"email", "STRING"});
    studentdb.alterTable("student", "DROP", {"cgpa", ""});
    studentdb.alterTable("student", "RENAME", "cgpa", "CGPA");
    studentdb.alterTable("student", "MODIFY", {"cgpa", "FLOAT"});

    studentdb.renameTable("studnet", "studentInfo");
	studentdb.dropTable("student", true); // true for cascade



}
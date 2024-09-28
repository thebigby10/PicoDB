#include<bits/stdc++.h>
#include "../include/PicoDB/PicoDB.h"

int main(){
	PicoDB studentdb("studentdb", "/home/thebigby01/tempdb/");
	studentdb.createTable("student", {
		{"student_id", "INT", "PRIMARY_KEY"},
		{"student_name", "STRING", "NOT_NULL"},
		{"cgpa", "DOUBLE",""},
	});
	
	studentdb.insertData("student", {"student_id", "student_name", "cgpa"}, {"220042152", "Asif", 0.00});
	studentdb.insertData("student", {"student_id", "student_name", "cgpa"}, {"220042153", "Uthuth", 4.00});
	
	studentdb.saveDB();

	studentdb.selectData("student", {});
	studentdb.selectData("student", {"student_id", "cgpa"});

	studentdb.dropTable("student");
}
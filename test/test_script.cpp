#include<bits/stdc++.h>
#include "../include/PicoDB/PicoDB.h"

int main(){
	// create db or use db
	PicoDB studentdb("studentdb", "/home/thebigby01/", "thebigby01", 152);
	
	// // create table
	// studentdb.createTable("student", {
	// 	{"student_id", "INT", "PRIMARY_KEY", ""},
	// 	{"student_name", "STRING", "NOT_NULL", ""},
	// 	{"cgpa", "INT","DEFAULT 0", }, 
	// });
	
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



}
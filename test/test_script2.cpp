#include<bits/stdc++.h>
#include "../include/PicoDB/PicoDB.h"
#include "../src/FileHandler.cpp"

using namespace std;
int main(){
	// create db or use db
	PicoDB barbiedb("barbiedb", "/home/thebigby01/db/barbiedb", "asif152", "_key_", ",_,");
	barbiedb.createTable(String("person_info"), {
		{"id", "INT", "PRIMARY_KEY", ""},
		{"name", "STRING", "NOT_NULL", ""} 
	});
	//check file exists
	// FileHandler file1("/home/thebigby01/db/barbiedb/barbiedb.config");
	// cout<<file1.fileExists()<<endl;
	barbiedb.saveDB();
}

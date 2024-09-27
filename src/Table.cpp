#include<iostream>
#include<string>
#include<vector>
#include "Cell.cpp"

using namespace std;

class Table{
private:
	string table_name;
	vector<vector< Cell> > table_data;
public:
	Table(string table_name);
};
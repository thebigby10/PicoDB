#include<iostream>
#include<string>
#include<vector>
using namespace std;

enum class DataType {
    INTEGER,
    DOUBLE,
    STRING,
    BOOLEAN,
    //DATE
};

enum class Constraint {
    PRIMARY_KEY,
    NOT_NULL,
    UNIQUE,
    NONE,
    //FOREIGN KEY
    
};

class Cell{
public:
	Cell(int data){
		this->data_i = data;
		this->datatype = DataType::INTEGER;
	};
	Cell(double data){
		this->data_d = data;
		this->datatype = DataType::DOUBLE;
	};
	Cell(string data){
		this->data_s = data;
		this->datatype = DataType::STRING;
	};
	Cell(bool data){
		this->data_b = data;
		this->datatype = DataType::BOOLEAN;
	};
	DataType getDatatype() const {
    	return datatype;
    }
private:
	DataType datatype;
	//data field:
	int data_i;
	double data_d;
	string data_s;
	bool data_b;
	//implement date
    Constrains constrains;
};
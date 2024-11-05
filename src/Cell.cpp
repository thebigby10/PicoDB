#ifndef CELL_H // Include guard
#define CELL_H
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

class Cell{
public:
    // Default constructor - compile hoy na naile, pore thik korte hobe
    Cell() : data_i(0), data_d(0.0), data_b(false), datatype(DataType::STRING) {
        // Alternatively, you could set datatype to a more appropriate type if needed
    }

	Cell(int data){
		this->data_i = data;
		this->datatype = DataType::INTEGER;
	};
	Cell(double data){
		this->data_d = data;
		this->datatype = DataType::DOUBLE;
	};
	Cell(String data){
		this->data_s = data;
		this->datatype = DataType::STRING;
	};
	Cell(bool data){
		this->data_b = data;
		this->datatype = DataType::BOOLEAN;
	};

    // Getters for each data type
    DataType getDataType() const {return datatype;}

    int getInt() const {return data_i;}

    double getDouble() const {return data_d;}

    String getString() const {return data_s;}

    bool getBoolean() const {return data_b;}

private:
	DataType datatype;
	//data field:
	int data_i;
	double data_d;
	String data_s;
	bool data_b;
	//implement date
    // Constrains constrains;
};
#endif

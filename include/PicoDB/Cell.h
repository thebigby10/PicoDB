#ifndef CELL_H // Include guard
#define CELL_H
#include<iostream>
#include "String.h"
#include "Vector.h"
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
    //Cell() : data_i(0), data_d(0.0), data_b(false), datatype(DataType::STRING) {
    // Alternatively, you could set datatype to a more appropriate type if needed
    //}

	// alternative default constructor
	Cell() : datatype(DataType::STRING), data_s("") {}

	Cell(int data){
		this->data_i = data;
		this->datatype = DataType::INTEGER;
	};
	Cell(double data){
		this->data_d = data;
		this->datatype = DataType::DOUBLE;
	};
	// Cell(String data){
	// 	this->data_s = data;
	// 	this->datatype = DataType::STRING;
	// };
	Cell(bool data){
		this->data_b = data;
		this->datatype = DataType::BOOLEAN;
	};

	Cell(const String& data) {
        if (data == String("true") || data == String("false")) {
            datatype = DataType::BOOLEAN;
            data_b = (data == String("true"));
        } else if (isInteger(data)) {
            datatype = DataType::INTEGER;
            data_i = data.toInt();
        } else if (isDouble(data)) {
            datatype = DataType::DOUBLE;
            data_d = data.toDouble();
        } else {
            datatype = DataType::STRING;
            data_s = data;
        }
    }

	// Function to get data based on the datatype
	String getData() const {
		switch (datatype) {
			case DataType::INTEGER:
				return String::toString(data_i);
			case DataType::DOUBLE:
				return String::toString(data_d);
			case DataType::BOOLEAN:
				return data_b ? String("true") : String("false");
			case DataType::STRING:
				return data_s;
			default:
				return String("Unknown DataType");
		}
	}

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

	bool isInteger(const String& str) const {
        for (size_t i = 0; i < str.length(); ++i) {
            if (i == 0 && str[i] == '-') continue;
            if (str[i] < '0' || str[i] > '9') return false;
        }
        return !str.empty();
    }

    bool isDouble(const String& str) const {
        bool decimalPoint = false;
        for (size_t i = 0; i < str.length(); ++i) {
            if (i == 0 && str[i] == '-') continue;
            if (str[i] == '.') {
                if (decimalPoint) return false;
                decimalPoint = true;
            } else if (str[i] < '0' || str[i] > '9') {
                return false;
            }
        }
        return decimalPoint;
    }

	//implement date
    // Constrains constrains;
};
#endif

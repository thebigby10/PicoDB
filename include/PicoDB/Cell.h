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
};

class Cell {
public:
    DataType datatype;
    int data_i;
    double data_d;
    String data_s;
    bool data_b;

    Cell() : data_i(0), data_d(0.0), data_b(false), datatype(DataType::STRING) {}

    Cell(int data) : data_i(data), datatype(DataType::INTEGER) {}
    Cell(double data) : data_d(data), datatype(DataType::DOUBLE) {}
    Cell(bool data) : data_b(data), datatype(DataType::BOOLEAN) {}

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

    DataType getDataType() const { return datatype; }
    int getInt() const { return data_i; }
    double getDouble() const { return data_d; }
    String getString() const { return data_s; }
    bool getBoolean() const { return data_b; }

private:
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
};

#endif

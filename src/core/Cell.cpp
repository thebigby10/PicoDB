#include "../../include/PicoDB/Cell.h"

// Getters for each data type
DataType Cell::getDataType() const { return datatype;}

int Cell::getInt() const {return data_i;}

double Cell::getDouble() const {return data_d;}

String Cell::getString() const {return data_s;}

bool Cell::getBoolean() const {return data_b;}

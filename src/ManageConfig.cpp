#ifndef MANAGECONFIG_H // Include guard start
#define MANAGECONFIG_H
#include "String.cpp"
#include <fstream>

class ManageConfig{
private:
	String db_path;
public:
	ManageConfig(String db_path){
		this->db_path = db_path;
	}

}

#endif
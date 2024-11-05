#ifndef DATABASE_H // Include guard start
#define DATABASE_H
#include<iostream>
#include<filesystem>
#include "Vector.cpp"
#include "Encryptor.cpp"
#include "String.cpp"
#include "Table.cpp"
#include "FileHandler.cpp"
#include "Cell.cpp"
#include "ConfigManager.cpp"
#include "StringVectorConverter.cpp"

		this->db_name = db_name;
		this->db_path = db_path;
		this->username = username;
		this->key = key;
		this->delimiter = delimiter;
		this->admin = username;
		//check if file exists
		FileHandler conf_file = FileHandler(db_path+String("/")+db_name+String(".config")); //path to config file
		if(conf_file.fileExists()){
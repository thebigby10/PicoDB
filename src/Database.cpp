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
			// Conf manager fetches raw data ✅
			ConfigManager conf_manager(db_path+String("/")+db_name+String(".config"));

			// convert the config file into variables
			this->delimiter = conf_manager.get_t_delimiter();
			this->admin = conf_manager.get_admin();
			//this->db_data = conf_manager.get_table_header();
			// TODO : must check if the user exists

			//convert the tables into vector ✅
			loadCurrentTables(db_name, db_path);
		}
		else{
			//create config file
			ConfigManager conf_manager(db_path+String("/")+db_name+".config");
			conf_manager.createConfig(db_name,table_delimiter,username );
		}
	};
	// Database e(string db_name, bool encryption);

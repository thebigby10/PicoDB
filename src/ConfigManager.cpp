#ifndef MANAGECONFIG_H // Include guard start
#define MANAGECONFIG_H
#include "String.cpp"
#include "Map.cpp"
#include "Vector.cpp"
#include "FileHandler.cpp"
#include <fstream>

class ConfigManager{
private:
	String db_path;
public:
	ConfigManager(String db_path){
		this->db_path = db_path;
	}
	void writeConfig(String database_name, String conf_path, String table_delimiter, String admin_username, bool encryption = true ){
		String conf_data;
		conf_data+=String("[Database]\n");
		conf_data+=String("database_name = ") + database_name + String("\n"); //Check
		conf_data+=String("file_path = ") + conf_path + String("\n");
		conf_data+=String("table_delimiter = ") + table_delimiter + String("\n");
		conf_data+=String("\n");
		conf_data+=String("[Admin]\n");
		conf_data+=String("username = ") + admin_username + String("\n");
		conf_data+=String("\n");
		conf_data+=String("[Permission]\n");
		conf_data+=String("\n");
		conf_data+=String("[Encryption]\n");
		if(encryption) conf_data+=String("enabled = true\n");
		else conf_data+=String("enabled = false\n");
		conf_data+=String("\n");
		conf_data+=String("[Tables]\n");

		FileHandler conf_file(conf_path);
		conf_file.writeToFile(conf_data);

	}
	// Vector<Map<String, String>> readConfig(){

	// }

};

#endif
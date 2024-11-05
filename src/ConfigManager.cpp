#ifndef MANAGECONFIG_H // Include guard start
#define MANAGECONFIG_H
#include "String.cpp"
//#include "Map.cpp"
#include "Vector.cpp"
#include "FileHandler.cpp"
#include "Table.cpp"
#include <fstream>

class ConfigManager{
private:
	String conf_path;
	String conf_data;
public:
	ConfigManager(String file_path){
		this->conf_path = file_path;
		FileHandler conf_file(conf_path);
		if(conf_file.fileExists()){
			this->conf_data = conf_file.readFromFile();
		}
	}
	void createConfig(String database_name, String table_delimiter, String admin_username, bool encryption = true ){
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
        f(encryption) conf_data+=String("enabled = true\n");
		else conf_data+=String("enabled = false\n");
		conf_data+=String("\n");
		conf_data+=String("[Tables]\n");

		FileHandler conf_file(conf_path);
		conf_file.writeToFile(conf_data);
	}

	void updateConfig(String new_config_data){
		this->conf_data = new_config_data; //update the config data
		FileHandler conf_file(conf_path);
		conf_file.writeToFile(new_config_data); //write the new config data to the file
	}

	void appendConfig(String new_config_data, bool append){
		FileHandler conf_file(conf_path);
		conf_file.writeToFile(new_config_data, append); //append the updated config data to the file
	}

	String get_t_delimiter() {
        int start_pos = conf_data.findSubstring(String("table_delimiter = "));
        if (start_pos == -1) return String(""); // Not found
        start_pos += String("table_delimiter = ").length();

        // Manually find the end position (next newline character after start_pos)
        int end_pos = start_pos;
        while (end_pos < conf_data.length() && conf_data[end_pos] != '\n') {
            ++end_pos;
        }

        return conf_data.substr(start_pos, end_pos - start_pos); // Extract the delimiter value
    }

    String get_admin() {
        int start_pos = conf_data.findSubstring(String("username = ")); // Find the start of the admin username
        if (start_pos == -1) return String(""); // Not found
        start_pos += String("username = ").length(); // move to the start of the username

#ifndef MANAGECONFIG_H // Include guard start
#define MANAGECONFIG_H
#include "String.cpp"
#include "Map.cpp"
#include "Vector.cpp"
#include "FileHandler.cpp"
#include "Table.cpp"
#include <fstream>

class ConfigManager{
private:
	String conf_path;
	String conf_data;
public:
	ConfigManager(String db_path){
		this->conf_path = conf_path;
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
		if(encryption) conf_data+=String("enabled = true\n");
		else conf_data+=String("enabled = false\n");
		conf_data+=String("\n");
		conf_data+=String("[Tables]\n");

		FileHandler conf_file(conf_path);
		conf_file.writeToFile(conf_data);

	}
	void updateConfig(String new_config_data){
		this->conf_data = new_config_data; //update the config data
		FileHandler conf_file(conf_path); //write the new config data to the file
		conf_file.writeToFile(new_config_data); //write the new config data to the file

	}
		

	
	 String get_t_delimiter() {
		istringstream conf_data_stream(conf_data.c_str()); 
		string line; 
		while(getline(conf_data_stream, line)){ 
			if(line.find("table_delimiter") != string::npos){ 
				return String(line.substr(line.find("=")+1).c_str()); //return the table_delimiter
			}
		}
		return String(""); //return empty string if the table_delimiter is not found
		
	 }

	
	String get_admin(){
		istringstream ss(conf_data.c_str());
		string line;
		while(getline(ss, line)){
			if(line.find("username") != string::npos){
				return String(line.substr(line.find("=")+1).c_str());
			}
		}
		return String("");//return empty string if the admin is not found

		
	}
	String get_delimiter(){
		istringstream ss(conf_data.c_str());
		string line;
		while(getline(ss, line)){
			if(line.find("delimiter") != string::npos){
				return String(line.substr(line.find("=")+1).c_str());
			}
		}
		return String("");//return empty string if the delimiter is not found

	}
	Vector<Map<String, Vector<String> > > get_users(){
		//returns a vector in format Vector<Map<String, Vector<String> > >; 
		//username, tables
	}
	// is_encrypted()
	Vector<String> get_table_header(){
		//gets the tables and converts them in a Vector<Table> and returns it
	}
	void deleteConfig(){
		
	}

};

#endif
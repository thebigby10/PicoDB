#ifndef MANAGECONFIG_H // Include guard start
#define MANAGECONFIG_H

#include "String.h"
#include "Map.h"
#include "Vector.h"
#include "FileHandler.h"
#include "Table.h"
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
	void createConfig(String database_name, String table_delimiter, String admin_username, bool encryption = true );

	void updateConfig(String new_config_data);

	void appendConfig(String new_config_data, bool append);

	String get_t_delimiter() ;

    String get_admin() ;

    /*
	Map<String, Vector<String>>  get_users()*/

// always returns true - could lead to bugs
	bool is_encrypted();

	Vector<Vector<String>> get_table_meta_data();


	Vector<String> get_table_names() ;

	void deleteConfig();

};

#endif

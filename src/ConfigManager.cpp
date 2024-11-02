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

        // Find the end of the admin username (next newline)
        int end_pos = start_pos; // Start from the beginning of the username
        while (end_pos < conf_data.length() && conf_data[end_pos] != '\n') { // Find the next newline character
            ++end_pos; // Move to the next character
        }

        return conf_data.substr(start_pos, end_pos - start_pos); // Extract the admin username


    }


	Vector<Map<String, Vector<String> > > get_users(){
		//returns a vector in format Vector<Map<String, Vector<String> > >;
		//username, tables
		Vector<Map<String, Vector<String>>> users;
        Map<String, Vector<String>> user_tables;

        // Find the start position of the [Permission] section in conf_data
        int start_pos = conf_data.findSubstring(String("[Permission]"));
        if (start_pos == -1) return users; // Return an empty vector if no [Permission] section is found

        // Move the start position to after "[Users]"
        start_pos += String("[Permission]").length();

        // Read each line until the next section or end of conf_data
        while (start_pos < conf_data.length() && conf_data[start_pos] != '[') {
            int end_pos = start_pos;
            while (end_pos < conf_data.length() && conf_data[end_pos] != '\n') {
                ++end_pos;
            }

            // Extract a single line
            String line = conf_data.substr(start_pos, end_pos - start_pos);

            // Find the delimiter '='
            int equal_pos = line.find('=');
            if (equal_pos != -1) {
                // Extract username
                String username = line.substr(0, equal_pos).trim();

                // Extract the tables string and split by comma
                String tables_str = line.substr(equal_pos + 1, end_pos - (equal_pos+1)).trim();
                Vector<String> tables;

                // Split tables_str by ',' to get each table name
                size_t pos = 0;
                while ((pos = tables_str.find(',')) != -1) {
                    tables.push_back(tables_str.substr(0, pos).trim());
                    tables_str = tables_str.substr(pos + 1, tables_str.strLength()-(pos+1));
                }
                tables.push_back(tables_str.trim()); // Last table after the last comma

                // Add the username and tables to the map
                user_tables[username] = tables;
            }

            // Move to the next line
            start_pos = end_pos + 1;
        }

        // Add the map to the users vector
        users.push_back(user_tables);
        return users;
	}

	bool is_encrypted(){

	}



	Vector<String> get_table_header(){
		//gets the tables and converts them in a Vector<Table> and returns it
		Vector<String> table_headers;
		int start_pos = conf_data.findSubstring(String("[Tables]"));
		if(start_pos == -1) return table_headers;

		start_pos += String("[Tables]").length();
		while (start_pos < conf_data.length() &&  conf_data[start_pos] != '[') {
			int end_pos = start_pos;
			while (end_pos < conf_data.length() && conf_data[end_pos] != '\n') {
				++end_pos;
			}
			String table_line = conf_data.substr(start_pos, end_pos - start_pos);
			table_headers.push_back(conf_data.substr(start_pos, end_pos - start_pos));
			start_pos = end_pos + 1;
		}
		return table_headers;

	}


	Vector<String> get_table_names() {

	}


	void deleteConfig(){
		FileHandler conf_file(conf_path);
		conf_file.removeFile();

	}

};

#endif

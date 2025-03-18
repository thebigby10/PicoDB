#ifndef CONFIG_MANAGER_H // Include guard start
#define CONFIG_MANAGER_H

#include "String.h"
#include "Vector.h"
#include "FileHandler.h"
#include "Table.h"

class ConfigManager {
private:
	String conf_path;
	String conf_data;

public:
	// Constructor
	ConfigManager(String file_path) {
		this->conf_path = file_path;
		FileHandler conf_file(conf_path);
		if (conf_file.fileExists()) {
			this->conf_data = conf_file.readFromFile();
		}
	}

	// Create a new config file
	void createConfig(String database_name, String table_delimiter, String admin_username, bool encryption) {
		String conf_data;
		conf_data += String("[Database]\n");
		conf_data += String("database_name = ") + database_name + String("\n"); //Check
		conf_data += String("file_path = ") + conf_path + String("\n");
		conf_data += String("table_delimiter = ") + table_delimiter + String("\n");
		conf_data += String("\n");
		conf_data += String("[Admin]\n");
		conf_data += String("username = ") + admin_username + String("\n");
		conf_data += String("\n");
		conf_data += String("[Permission]\n");
		conf_data += String("\n");
		conf_data += String("[Encryption]\n");
		if (encryption) conf_data += String("enabled = true\n");
		else conf_data += String("enabled = false\n");
		conf_data += String("\n");
		conf_data += String("[Tables]\n");

		FileHandler conf_file(conf_path);
		conf_file.writeToFile(conf_data);
	}

	// Update the config file with new data
	void updateConfig(String new_config_data) {
		this->conf_data = new_config_data; // Update the config data
		FileHandler conf_file(conf_path);
		conf_file.writeToFile(new_config_data); // Write the new config data to the file
	}

	// Append new data to the config file
	void appendConfig(String new_config_data, bool append) {
		FileHandler conf_file(conf_path);
		conf_file.writeToFile(new_config_data, append); // Append the updated config data to the file
	}

	// Get table delimiter from config file
	String get_t_delimiter() {
		int start_pos = conf_data.findSubstring(String("table_delimiter = "));
		if (start_pos == -1) return String(""); // Not found
		start_pos += String("table_delimiter = ").length();

		// Find end position (newline character after start_pos)
		int end_pos = start_pos;
		while (end_pos < conf_data.length() && conf_data[end_pos] != '\n') {
			++end_pos;
		}

		return conf_data.substr(start_pos, end_pos - start_pos); // Extract the delimiter value
	}

	// Get user permissions
	Vector<Vector<String>> get_permissions() {
		Vector<Vector<String>> permissions;

		// Find the start position of the [Permission] section in conf_data
		int start_pos = conf_data.findSubstring(String("[Permission]"));
		if (start_pos == -1) return permissions; // Return an empty vector if no [Permission] section is found

		// Move the start position to after "[Permission]"
		start_pos += String("[Permission]").length();

		// Read each line until the next section or end of conf_data
		while (start_pos < conf_data.length() && conf_data[start_pos] != '[') {
			int end_pos = start_pos;
			
			// Find the end of the current line
			while (end_pos < conf_data.length() && conf_data[end_pos] != '\n') {
				++end_pos;
			}

			// Extract a single line
			String line = conf_data.substr(start_pos, end_pos - start_pos).trim();

			// Skip empty lines
			if (line.length() > 0) {
				Vector<String> line_data;
				int pos = 0;

				// Split the line by commas
				while ((pos = line.find(',')) != -1) {
					line_data.push_back(line.substr(0, pos).trim());
					line = line.substr(pos + 1, line.length() - (pos + 1));
				}

				// Add the last segment (after the last comma)
				if (line.length() > 0) {
					line_data.push_back(line.trim());
				}

				// Add non-empty parsed line to permissions
				permissions.push_back(line_data);
			}

			// Move to the next line
			start_pos = end_pos + 1;
		}

		return permissions;
	}

	// Get admin username
	String get_admin() {
		int start_pos = conf_data.findSubstring(String("username = ")); // Find the start of the admin username
		if (start_pos == -1) return String(""); // Not found
		start_pos += String("username = ").length(); // Move to the start of the username

		// Find the end of the admin username (next newline)
		int end_pos = start_pos; // Start from the beginning of the username
		while (end_pos < conf_data.length() && conf_data[end_pos] != '\n') { // Find the next newline character
			++end_pos; // Move to the next character
		}

		return conf_data.substr(start_pos, end_pos - start_pos); // Extract the admin username
	}

	// Check if encryption is enabled
	bool is_encrypted() {
		int start_pos = conf_data.findSubstring(String("enabled = "));
		if (start_pos == -1) return false; // Return false if encryption is not specified
		start_pos += String("enabled = ").length();
		return conf_data.substr(start_pos, 4) == String("true");
	}

	// Get metadata of all tables
	Vector<Vector<String>> get_table_meta_data() {
		Vector<Vector<String>> table_meta_data;

		// Find the start position of the [Tables] section in conf_data
		int start_pos = conf_data.findSubstring(String("[Tables]"));
		if (start_pos == -1) return table_meta_data; // Return an empty vector if no [Tables] section is found

		// Move the start position to after "[Tables]"
		start_pos += String("[Tables]").length();

		// Read each line until the next section or end of conf_data
		while (start_pos < conf_data.length() && conf_data[start_pos] != '[') {
			int end_pos = start_pos;
			while (end_pos < conf_data.length() && conf_data[end_pos] != '\n') {
				++end_pos;
			}

			// Extract a single line
			String line = conf_data.substr(start_pos, end_pos - start_pos).trim();

			// Skip empty lines
			if (line.length() > 0) {
				Vector<String> line_data;
				int pos = 0;

				// Split the line by commas
				while ((pos = line.find(',')) != -1) {
					line_data.push_back(line.substr(0, pos).trim());
					line = line.substr(pos + 1, line.length() - (pos + 1));
				}
				line_data.push_back(line.trim());

				// Add the parsed line to the metadata
				table_meta_data.push_back(line_data);
			}

			// Move to the next line
			start_pos = end_pos + 1;
		}

		return table_meta_data;
	}

	// Get names of all tables
	// Vector<String> get_table_names();

	// Delete the config file
	void deleteConfig() {
		FileHandler conf_file(conf_path);
		conf_file.removeFile();
	}

};

#endif // CONFIG_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
using namespace std;

class Database {
public:
    Database(string db_name, string db_path) {
        this->db_name = db_name;
        this->file_path = db_path;

        // Check if the database file exists
        bool exists = checkFileExists(file_path + "/" + db_name + ".db");
        if (exists) {
            // Load data from the database file
            cout << "Database found. Loading data..." << endl;
            loadDatabase();
        } else {
            // Create a new database file
            cout << "Database not found. Creating new database at " << db_path << endl;
            createDatabaseFile();
        }
    }

    bool createTable(string tableName, vector < vector < string > > columnData) {
        // Create a 2D vector to store column data
        vector < vector < string > > table;

        // Add each column definition to the table
        for (const auto& column : columnData) {
            table.push_back(column);
        }

        // Add the table to the database 
        db_data.push_back(table); // this vector is 3D

        // Simulate saving table info
        cout << "Table '" << tableName << "' created successfully with the following columns:" << endl;
        for (const auto& column : columnData) {
            cout << "Column: " << column[0] << " | Type: " << column[1] << " | Constraints: ";
            for (size_t i = 2; i < column.size(); ++i) {
                cout << column[i] << " ";
            }
            cout << endl;
        }

        return true; // Assume table creation is always successful for now
    }

private:
    string db_name; 
    string file_path = "";
    bool encryption = true;
    vector < vector < vector < string > > > db_data; // 3D vector

    bool checkFileExists(string file_path) {
        //return filesystem::exists(file_path);
    }

    void createDatabaseFile() {
        // Ensure the directory exists
        // if (!filesystem::exists(file_path)) {
        //     cerr << "Error: The specified directory does not exist: " << file_path << endl;
        //     return; // Exit if the directory does not exist
        // }

        // Create a new database file
        cout << "Creating new database file..." << endl;

        ofstream db_file(file_path + "/" + db_name + ".db"); // Create an output file stream
        if (db_file.is_open()) {
            db_file << "DATABASE: " << db_name << endl; // Initial placeholder content
            db_file << "Tables:" << endl; // Placeholder for future tables
            db_file.close();
            cout << "Database file '" << db_name << ".db' created successfully in " << file_path << "." << endl;
        } else {
            cerr << "Error creating database file '" << db_name << ".db'." << endl;
        }
    }

    void loadDatabase() {
        ifstream db_file(file_path + "/" + db_name + ".db"); // Create an input file stream
        if (!db_file) { // Check if the file opened successfully
            cerr << "Error opening database file for reading." << endl;
            return; // Exit if the file cannot be opened
        }

        string line;
        while (getline(db_file, line)) {
            // Process the line to extract table data (this is simplified)
            vector<string> tableData;
            stringstream ss(line);
            string item;

            while (getline(ss, item, ',')) {
                tableData.push_back(item);
            }
            // Add to the database (you may need more sophisticated logic here)
           // db_data.push_back( (vector < vector <string> >){ { tableData }});
        }

        db_file.close();
    }

    void saveDatabase() {
        ofstream db_file(file_path + "/" + db_name + ".db"); // Create an output file stream
        if (!db_file) { // Check if the file was opened successfully
            cerr << "Error opening database file for writing." << endl;
            return; // Exit if the file cannot be opened
        }

        for (const auto& table : db_data) {
            for (const auto& column : table) {
                // Join column data into a single line
                string line;
                for (const auto& item : column) {
                    line += item + ",";
                }
                // Remove trailing comma
                if (!line.empty()) {
                    line.pop_back();
                }
                db_file << line << endl;
            }
        }

        db_file.close();
        cout << "Database saved successfully." << endl;
    }
};

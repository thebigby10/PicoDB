#ifndef FILEUTILS_H // Include guard start
#define FILEUTILS_H
#include "String.h"
#include <fstream>

class FileHandler{
private:
    String filepath;
public:
//checks if a file exists
    FileHandler(String filepath){
        this->filepath = filepath;
    }

    bool fileExists() ;
// Function to read from a file and return a single String containing all its contents
    String readFromFile() ;
    // Function to write data to a file (same as before)
    // The 'append' flag determines if the data should overwrite (false) or append (true) to the file
    void writeToFile( const String& data, bool append = false) ;
    // Function to create a file (it will overwrite if the file already exists)
    void createFile() ;
    // Function to delete a file
    bool removeFile();
};

#endif

#ifndef FILEUTILS_H // Include guard start
#define FILEUTILS_H
#include "String.cpp"
#include <cstdio>
#include <memory>
#include <stdexcept>

// Migrate to an oop

//only windows and linux supported

#ifdef _WIN32
    #define FILE_EXISTS_CMD(filename) (String("if exist ") + filename + String(" echo exists"))
    #define READ_FILE_CMD(filename) (String("type ") + filename)
#else
    #define FILE_EXISTS_CMD(filename) (String("test -f ") + filename + String(" && echo exists"))
    #define READ_FILE_CMD(filename) (String("cat ") + filename)
#endif

Vector<String> executeCommand(const String& command) {
        Vector<String> outputLines;
        char buffer[128];  // Buffer to store each line of output
        FILE* pipe = popen(command.c_str(), "r");  // Open the process to execute command
        
        if (!pipe) {
            std::cerr << "popen() failed!" << std::endl;
            return outputLines;
        }
        
        // Read the output line by line and append to the Vector<String>
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            String line(buffer);
            outputLines.push_back(line);
        }
        
        // Close the pipe
        pclose(pipe);
        return outputLines;
    }


bool fileExists(const String& filename) {
    String command = FILE_EXISTS_CMD(filename);
    Vector<String> result = executeCommand(command);
    
    // If the result contains "exists", the file exists
    if (result.get_size() > 0) {
    	result[0].trim();
    	if(result[0] == String("exists"))
        	return true;
    }
    return false;
}

#endif
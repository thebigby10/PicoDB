#ifndef FILEUTILS_H // Include guard start
#define FILEUTILS_H
#include "String.cpp"
#include <fstream>

// Migrate to an oop

//checks if a file exists
bool fileExists(const String& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Function to read from a file and return a single String containing all its contents
String readFromFile(const String& filename) {
    std::ifstream fileStream(filename.c_str(), std::ios::in);  // Open the file in input mode
    
    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return String("");  // Return an empty string on failure
    }

    String fileContent;  // To store the whole file content
    char buffer[256];    // Buffer to read each line

    // Read the file line by line and append it to the String object
    while (fileStream.good()) {
        fileStream.getline(buffer, 256);
        fileContent += String(buffer);  // Append the current line to fileContent
        fileContent += "\n";            // Append newline to maintain formatting
    }
    
    fileStream.close();  // Close the file
    return fileContent;
}

#endif
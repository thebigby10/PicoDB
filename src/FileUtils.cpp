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

// Function to write data to a file (same as before)
// The 'append' flag determines if the data should overwrite (false) or append (true) to the file
void writeToFile(const String& filename, const String& data, bool append = false) {
    std::ofstream fileStream;
    
    // Choose file mode based on append flag
    if (append) {
        fileStream.open(filename.c_str(), std::ios::app);  // Open file in append mode
    } else {
        fileStream.open(filename.c_str(), std::ios::out);  // Open file in write/overwrite mode
    }
    
    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    
    // Write the entire string to the file
    fileStream << data;
    
    fileStream.close();  // Close the file
}

#endif
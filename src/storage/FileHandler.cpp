#include "../../include/PicoDB/FileHandler.h"

bool FileHandler::fileExists() {
    std::ifstream file(filepath);
    return file.good();
}
// Function to read from a file and return a single String containing all its contents
String FileHandler::readFromFile() {
    std::ifstream fileStream(filepath.c_str(), std::ios::in);  // Open the file in input mode

    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
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
void FileHandler::writeToFile(const String& data, bool append = false) {
    std::ofstream fileStream;

    // Choose file mode based on append flag
    if (append) {
        fileStream.open(filepath.c_str(), std::ios::app);  // Open file in append mode
    } else {
        fileStream.open(filepath.c_str(), std::ios::out);  // Open file in write/overwrite mode
    }

    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    // Write the entire string to the file
    fileStream << data;

    fileStream.close();  // Close the file
}
// Function to create a file (it will overwrite if the file already exists)
void FileHandler::createFile() {
    std::ofstream fileStream(filepath.c_str(), std::ios::out);  // Open file in write mode (creates file)

    if (!fileStream.is_open()) {
        std::cerr << "Failed to create file: " << filepath << std::endl;
    }

    fileStream.close();  // Close the file
}
// Function to delete a file
bool FileHandler::removeFile() {
    // Remove the file using std::remove, return true if successful, false otherwise
    if (std::remove(filepath.c_str()) == 0) {
        return true;
    } else {
        std::cerr << "Failed to delete file: " << filepath << std::endl;
        return false;
    }
}

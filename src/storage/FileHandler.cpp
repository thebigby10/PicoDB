#include "../../include/PicoDB/FileHandler.h"

// // Constructor
// FileHandler::FileHandler(String filepath) {
//     this->filepath = filepath;
// }

// // Checks if a file exists
// bool FileHandler::fileExists() const {
//     std::ifstream file(filepath.c_str());
//     return file.good();
// }

// // Reads from a file and returns a String with the file's content
// String FileHandler::readFromFile() const {
//     std::ifstream fileStream(filepath.c_str(), std::ios::in);  // Open the file in read mode

//     if (!fileStream.is_open()) {
//         std::cerr << "Failed to open file: " << filepath << std::endl;
//         return String("");  // Return an empty string on failure
//     }

//     String fileContent;  // To store the whole file content
//     char buffer[256];    // Buffer to read each line

//     // Read the file line by line
//     while (fileStream.getline(buffer, 256)) {
//         fileContent += String(buffer) + "\n";  // Append line with newline
//     }

//     fileStream.close();  // Close the file
//     return fileContent;
// }

// // Writes data to a file (append mode or overwrite mode)
// void FileHandler::writeToFile(const String& data, bool append) const {
//     std::ofstream fileStream;

//     // Open file in appropriate mode
//     fileStream.open(filepath.c_str(), append ? std::ios::app : std::ios::out);

//     if (!fileStream.is_open()) {
//         std::cerr << "Failed to open file: " << filepath << std::endl;
//         return;
//     }

//     fileStream << data;  // Write data to the file
//     fileStream.close();  // Close the file
// }

// // Creates a new file (overwrites if it exists)
// void FileHandler::createFile() const {
//     std::ofstream fileStream(filepath.c_str(), std::ios::out);

//     if (!fileStream.is_open()) {
//         std::cerr << "Failed to create file: " << filepath << std::endl;
//     }

//     fileStream.close();
// }

// // Deletes the file
// bool FileHandler::removeFile() const {
//     if (std::remove(filepath.c_str()) == 0) {
//         return true;
//     } else {
//         std::cerr << "Failed to delete file: " << filepath << std::endl;
//         return false;
//     }
// }

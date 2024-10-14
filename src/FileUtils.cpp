#ifndef FILEUTILS_H // Include guard start
#define FILEUTILS_H
#include "String.cpp"
#include <fstream> 
#include<iostream>

// Migrate to an oop
bool fileExists(const String& filename) {
    std::ifstream file(filename);
    return file.good();
}

#endif
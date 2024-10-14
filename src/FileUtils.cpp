#ifndef FILEUTILS_H // Include guard start
#define FILEUTILS_H
#include "String.cpp"

// Migrate to an oop

//only windows and linux supported

bool fileExists(const String& filename) {
	#ifdef _WIN32  // For Windows
	    return system((String("if exist \"") + filename + String("\" exit 0")).c_str()) == 0;
	#elif __linux__  // For Linux
	    return system((String("test -e \"") + filename + String("\"")).c_str()) == 0;
	#else
	    return false;
	#endif
}

void readFromFile(const String& filename) {

}

#endif
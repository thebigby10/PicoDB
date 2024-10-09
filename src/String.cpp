#include<iostream>

class String{
private:
	char* data;
	size_t len;
	
	//helper function for calculating length of C string
	size_t strLength(const char* str) const {
        size_t length = 0;
        while (str[length] != '\0') {
            ++length;
        }
        return length;
    }
    //helper function to copy c string
    void strCopy(char* dest, const char* src) {
        size_t i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            ++i;
        }
        dest[i] = '\0'; // Null-terminate the copied string
    }

public:
//default constructor
	String() : data(new char[1]), len(0) {
        data[0] = '\0';
    }
//constructor from string
    String(const char* str) {
		len = strLength(str);
        data = new char[len + 1]; //allocate memory
        strCopy(data, str); //copy contents
    }
//copy constructor
    String(const String& other) {
        len = other.len;
        data = new char[len + 1];
        strCopy(data, other.data);
    }
//destructor
    ~String() {
        delete[] data;
    }
};
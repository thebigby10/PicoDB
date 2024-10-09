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
//assignment operator overloading
    String& operator=(const String& other) {
        if (this != &other) { //check for self assignment
            delete[] data;    //release old memory
            len = other.len;
            data = new char[len + 1];
            strCopy(data, other.data);
        }
        return *this;
    }
//concat string+string
    String operator+(const String& other) const {
        size_t new_len = len + other.len;
        char* new_data = new char[new_len + 1];

	// copy first string
        for (size_t i = 0; i < len; ++i) {
            new_data[i] = data[i];
        }
	// copy 2nd string
        for (size_t i = 0; i < other.len; ++i) {
            new_data[len + i] = other.data[i];
        }
        new_data[new_len] = '\0'; // null operator

        return String(new_data); // return the concat string
    }
//concat string+c string
    String operator+(const char* str) const {
        size_t str_len = strLength(str);
        size_t new_len = len + str_len;
        char* new_data = new char[new_len + 1];

        for (size_t i = 0; i < len; ++i) {
            new_data[i] = data[i];
        }

        for (size_t i = 0; i < str_len; ++i) {
            new_data[len + i] = str[i];
        }
        new_data[new_len] = '\0'; // null operator

        return String(new_data); // return concated string
    }
};
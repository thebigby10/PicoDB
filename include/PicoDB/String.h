#ifndef STRING_H // Include guard start
#define STRING_H
#include<iostream>
#include <sstream>
#include "Vector.h"

class String {
private:
    char* data;
    size_t size;

    // Helper function for calculating length of C string
    size_t strLength(const char* str) const;

    // Helper function to copy C string
    void strCopy(char* dest, const char* src) const;

public:
    // Default constructor
    String() : data(new char[1]), size(0) {
        data[0] = '\0';
    }

    // Constructor from string
    String(const char* str) {
        size = strLength(str);
        data = new char[size + 1]; // Allocate memory
        strCopy(data, str);
    }

    String(size_t count, char c) {
        size = count;
        data = new char[size + 1]; // +1 for null terminator
        for (size_t i = 0; i < size; ++i) {
            data[i] = c; // Fill with the character
        }
        data[size] = '\0'; // Null terminate the string
    }

    // Copy constructor
    String(const String& other) {
        size = other.size;
        data = new char[size + 1];
        strCopy(data, other.data);
    }

    // Destructor
    ~String() {
        delete[] data;
    }
    // Assignment operator
    String& operator=(const String& other);

    // Overload the + operator to support concatenation (String + String)
    String operator+(const String& other) const;

    // Overload the += operator (String += String)
    String& operator+=(const String& other);

    // Concatenation of String + const char*
    String operator+(const char* str) const;

    // Conversion to const char*
    operator const char*() const {
        return data;
    }

    // Length of the string
    size_t length() const;

    // Direct character access
    char& operator[](size_t index) ;

    const char& operator[](size_t index) const;

    // Equality operator overloading
    bool operator==(const String& other) const ;

    // Find a character in a string
    int find(char c) const ;

    // Find a substring
    int findSubstring(const String& substr) const ;

    // Return substring
    String substr(size_t start, size_t sub_len) const ;

    // Clear string
    void clear() ;

    // Trim leading and trailing spaces
    String trim() const ;

    // Split string by delimiter
    String* split(char delimiter, size_t& count) const ;

    // Join a vector of strings with a delimiter
    String join(const Vector<String>& vec, char d, size_t columnCount = 0) ;
    const char* c_str() const ;


    int toInt() ;
    // Convert String to double
    double toDouble() ;

    // Helper function to reverse a char array (used in intToString and doubleToString)
    static void reverse(char* str, size_t length);

    static String toString(int num);
    static String toString(double num);
    static String toString(bool val) ;

    bool empty() const {
        return size == 0;
    }

    bool operator==(const char* str) const {
        return *this == String(str); // Convert to String and compare
    }
};

// Helper function to reverse a char array (used in intToString and doubleToString)
/*
void reverse(char* str, size_t length) {
    size_t start = 0;
    size_t end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        ++start;
        --end;
    }
}*/
#endif

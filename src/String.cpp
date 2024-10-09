#include<iostream>
class String{
private:
	char* data;
	size_t len;

	//helper function for calculating length of C string : for direct assigning
	size_t strLength(const char* str) const {
        size_t length = 0;
        while (str[length] != '\0') {
            ++length;
        }
        return length;
    }
    //helper function to copy c string : for direct assigning
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
//length of the string
    size_t length() const {
        return len;
    }
//direct character access - for normal and const string
    char& operator[](size_t index) {
        return data[index];
    }

    const char& operator[](size_t index) const {
        return data[index];
    }
//equality operator overloading
    bool operator==(const String& other) const {
        if (len != other.len) return false;
        for (size_t i = 0; i < len; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }
//find a character in a string
    int find(char c) const {
        for (size_t i = 0; i < len; ++i) {
            if (data[i] == c) return i;
        }
        return -1; // Return -1 if character not found
    }
//find a substring
    int findSubstring(const String& substr) const {
        if (substr.len > len) return -1; //substring larger than the string: not possible

        for (size_t i = 0; i <= len - substr.len; ++i) {
            size_t j = 0;
            for (; j < substr.len; ++j) {
                if (data[i + j] != substr[j]) break;
            }
            if (j == substr.len) return i; //substring found
        }
        return -1; //no match
    }
//return substring
    String substr(size_t start, size_t sub_len) const {
        if (start >= len) return String(); //out of bound, return empty
        if (start + sub_len > len) sub_len = len - start; //resize if needed

        char* sub_data = new char[sub_len + 1];
        for (size_t i = 0; i < sub_len; ++i) {
            sub_data[i] = data[start + i];
        }
        sub_data[sub_len] = '\0';

        return String(sub_data);
    }
//clear string
    void clear() {
        delete[] data;
        data = new char[1];
        data[0] = '\0';
        len = 0;
    }
//trim leading and trailing space
    void trim() {
	//trim leading 
        size_t start = 0;
        while (start < len && data[start] == ' ') {
            ++start;
        }
	// trim trailing
        size_t end = len - 1;
        while (end > start && data[end] == ' ') {
            --end;
        }

        size_t new_len = end - start + 1;
        char* trimmed_data = new char[new_len + 1];
        for (size_t i = 0; i < new_len; ++i) {
            trimmed_data[i] = data[start + i];
        }
        trimmed_data[new_len] = '\0';

        delete[] data;
        data = trimmed_data;
        len = new_len;
    }
//split string by delimiter
    String* split(char delimiter, size_t& count) const {
        count = 1; //at least one substirng exists : full string
        for (size_t i = 0; i < len; ++i) {
            if (data[i] == delimiter) ++count;
        }

        String* result = new String[count];
        size_t start = 0, sub_idx = 0;

        for (size_t i = 0; i < len; ++i) {
            if (data[i] == delimiter) {
                result[sub_idx++] = substr(start, i - start);
                start = i + 1;
            }
        }
        result[sub_idx] = substr(start, len - start); //last substring

        return result;
    }
//join a vector of string with delimiter
};
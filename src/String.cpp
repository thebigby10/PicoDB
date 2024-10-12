#include<iostream>
#include"Vector.cpp"
class String{
private:
	char* data;
	size_t size;

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
	String() : data(new char[1]), size(0) {
        data[0] = '\0';
    }
//constructor from string
    String(const char* str) {
        size = 0;
        while (str[size] != '\0') size++;  // Calculate the size
        data = new char[size + 1];         // Allocate memory
        for (size_t i = 0; i < size; ++i) {
            data[i] = str[i];              // Copy characters
        }
        data[size] = '\0';                 // Null-terminate the string
    }

//copy constructor
    String(const String& other) {
        size = other.size;
        data = new char[size + 1];
        for(size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        data[size] = '\0';
    }
//destructor
    ~String() {
        delete[] data;
    }
//assignment operator overloading
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new char[size + 1];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            data[size] = '\0';
        }
        return *this;
    }
//Overload the + operator to support concatenation
     String operator+(const String& other) const {
        String result;
        result.size = size + other.size;
        result.data = new char[result.size + 1];
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i];
        }
        for (size_t i = 0; i < other.size; ++i) {
            result.data[size + i] = other.data[i];
        }
        result.data[result.size] = '\0';
        return result;
    }
// Overload the += operator
    String& operator+=(const String& other) {
        *this = *this + other;
        return *this;
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
// conversation to const char*
    operator const char*() const {
        return data;
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
        if (size != other.size) return false;
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
    static String join(const Vector<String>& vec, char delimiter, size_t columnCount = 0) {
    if (vec.get_size() == 0) return "";  // Return empty string if the vector is empty

    // Create the result string, initializing it with the first element in the vector
    String result = vec[0];  // Copy the first element
    size_t currentColumn = 1;

    for (size_t i = 1; i < vec.get_size(); ++i) {
        result += delimiter;  // Add the delimiter

        // Check if we need to insert a newline based on columnCount
        if (columnCount > 0 && currentColumn >= columnCount) {
            result += "\n";
            currentColumn = 0;  // Reset column count
        }

        result += vec[i];  // Add the next element
        ++currentColumn;   // Increment the current column count
    }

    return result;
}


};
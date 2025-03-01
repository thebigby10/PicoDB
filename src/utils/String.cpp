#include "../../include/PicoDB/String.h"

String& String::operator=( const String& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new char[size + 1];
        strCopy(data, other.data);
    }
    return *this;
}

// Overload the + operator to support concatenation (String + String)
String String::operator+( const String& other)  const {
    String result;
    result.size = size + other.size;
    result.data = new char[result.size + 1];
    strCopy(result.data, data); // Copy current string
    strCopy(result.data + size, other.data); // Concatenate other string
    return result;
}

// Overload the += operator (String += String)
String& String::operator+=( const String& other) {
    *this = *this + other;
    return *this;
}

// Concatenation of String +   char*
String String::operator+(const  char* str) const  {
    size_t str_len = strLength(str);
    size_t new_len = size + str_len;
    char* new_data = new char[new_len + 1];

    strCopy(new_data, data);          // Copy original string
    strCopy(new_data + size, str);    // Append C-string

    return String(new_data); // Return concatenated string
}

// Length of the string
size_t String::length() const  {
    return size;
}

// Direct character access
const char& String::operator[](size_t index)const {
    return data[index];
}

// Equality operator overloading
bool String::operator==( const String& other) const  {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

// Find a character in a string
int String::find(char c) const  {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] == c) return i;
    }
    return -1; // Return -1 if character not found
}

// Find a substring
int String::findSubstring( const String& substr) const  {
    if (substr.size > size) return -1; // Substring larger than the string: not possible

    for (size_t i = 0; i <= size - substr.size; ++i) {
        size_t j = 0;
        for (; j < substr.size; ++j) {
            if (data[i + j] != substr[j]) break;
        }
        if (j == substr.size) return i; // Substring found
    }
    return -1; // No match
}

// Return substring
String String::substr(size_t start, size_t sub_len) const  {
    if (start >= size) return String(); // Out of bound, return empty
    if (start + sub_len > size) sub_len = size - start; // Resize if needed

    char* sub_data = new char[sub_len + 1];
    for (size_t i = 0; i < sub_len; ++i) {
        sub_data[i] = data[start + i];
    }
    sub_data[sub_len] = '\0';

    return String(sub_data);
}

// Clear string
void String::clear() {
    delete[] data;
    data = new char[1];
    data[0] = '\0';
    size = 0;
}

// Trim leading and trailing spaces
String String::trim() const  {
    size_t start = 0;
    while (start < size && data[start] == ' ') ++start;

    size_t end = size - 1;
    while (end > start && data[end] == ' ') --end;

    size_t new_len = end - start + 1;
    char* trimmed_data = new char[new_len + 1];
    for (size_t i = 0; i < new_len; ++i) {
        trimmed_data[i] = data[start + i];
    }
    trimmed_data[new_len] = '\0';

    // Return a new String object with trimmed data
    return String(trimmed_data);
}

// Split string by delimiter
String* String::split(char delimiter, size_t& count) const  {
    count = 1; // At least one substring exists: full string
    for (size_t i = 0; i < size; ++i) {
        if (data[i] == delimiter) ++count;
    }

    String* result = new String[count];
    size_t start = 0, sub_idx = 0;

    for (size_t i = 0; i < size; ++i) {
        if (data[i] == delimiter) {
            result[sub_idx++] = substr(start, i - start);
            start = i + 1;
        }
    }
    result[sub_idx] = substr(start, size - start); // Last substring

    return result;
}

// Join a vector of strings with a delimiter
String String::join(const  Vector<String>& vec, char d, size_t columnCount) {
    if (vec.get_size() == 0) return "";  // Return empty string if the vector is empty
    String delimiter(1, d);
    String result = vec[0];  // Copy the first element
    size_t currentColumn = 1;

    for (size_t i = 1; i < vec.get_size(); ++i) {
        result += String(delimiter);  // Add the delimiter

        if (columnCount > 0 && currentColumn >= columnCount) {
            result += "\n";
            currentColumn = 1;  // Reset to 1 after newline
        } else {
            ++currentColumn;
        }

        result += vec[i];  // Add the next element
    }

    return result;
}
const  char* String::c_str() const   {
    return data;  // Return the data pointer
}

int String::toInt() {
    String str = data;
    int num = 0;
    bool isNegative = false;
    size_t i = 0;

    // Check for negative sign
    if (str[0] == '-') {
        isNegative = true;
        ++i;
    }

    // Convert each character to the corresponding digit
    for (; i < str.length(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            num = num * 10 + (str[i] - '0');
        } else {
            break;  // Stop if a non-digit is encountered
        }
    }

    return isNegative ? -num : num;
}
// Convert String to double
double String::toDouble() {
    String str = data;
    double num = 0.0;
    bool isNegative = false;
    bool hasDecimal = false;
    double decimalFactor = 0.1;
    size_t i = 0;

    // Check for negative sign
    if (str[0] == '-') {
        isNegative = true;
        ++i;
    }

    // Convert each character to the corresponding digit
    for (; i < str.length(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (hasDecimal) {
                num += (str[i] - '0') * decimalFactor;
                decimalFactor /= 10.0;
            } else {
                num = num * 10 + (str[i] - '0');
            }
        } else if (str[i] == '.' && !hasDecimal) {
            hasDecimal = true;  // Start processing decimals
        } else {
            break;  // Stop if a non-digit is encountered
        }
    }

    return isNegative ? -num : num;
}

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

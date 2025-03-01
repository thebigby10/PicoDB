#include "../include/PicoDB/String.h"
#include <iostream>
#include <cassert>

void testConstructors() {
    String s1;
    assert(s1.length() == 0);

    String s2("Hello");
    assert(s2.length() == 5);
    assert(s2 == String("Hello"));

    String s3(s2);
    assert(s3 == String("Hello"));
}

void testAssignment() {
    String s1 = "Hello";
    String s2;
    s2 = s1;
    assert(s2 == String("Hello"));
}

void testConcatenation() {
    String s1 = "Hello";
    String s2 = " World";
    String s3 = s1 + s2;
    assert(s3 == String("Hello World"));

    s1 += "!!!";
    assert(s1 == String("Hello!!!"));

    s1 = "Hello";
    s1 = s1 + '!';
    assert(s1 == String("Hello!"));
}

void testEquality() {
    String s1 = "test";
    String s2 = "test";
    String s3 = "different";

    assert(s1 == s2);
    assert(!(s1 == s3));
}

void testFind() {
    String s = "Hello World";
    assert(s.find('W') == 6);
    assert(s.find('Z') == -1);
    assert(s.findSubstring("World") == 6);
    assert(s.findSubstring("Test") == -1);
}

void testSubstring() {
    String s = "Hello World";
    String sub = s.substr(6, 5);
    assert(sub == String("World"));
}

void testTrim() {
    String s = "  Trim this  ";
    assert(s.trim() == String("Trim this"));
}

void testSplit() {
    String s = "one,two,three";
    size_t count;
    String* parts = s.split(',', count);
    assert(count == 3);
    assert(parts[0] == String("one"));
    assert(parts[1] == String("two"));
    assert(parts[2] == String("three"));
    delete[] parts;
}

void testConversion() {
    assert(String::toString(123) == String("123"));
    assert(String::toString(45.67) == String("45.670000"));
    assert(String::toString(true) == String("true"));
    assert(String("123").toInt() == 123);
    assert(String("45.67").toDouble() == 45.67);
}

int main() {
    testConstructors();
    testAssignment();
    testConcatenation();
    testEquality();
    testFind();
    testSubstring();
    testTrim();
    testSplit();
    testConversion();

    std::cout << "All String tests passed!" << std::endl;
    return 0;
}

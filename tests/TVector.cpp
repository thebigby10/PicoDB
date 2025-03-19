#include <iostream>
#include <cassert>
#include "../include/PicoDB/Vector.h"

void testVectorInsertion() {
    Vector<int> vec;

    // Test: Insert elements using push_back
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // Test: Ensure elements are inserted correctly
    assert(vec.at(0) == 10);
    assert(vec.at(1) == 20);
    assert(vec.at(2) == 30);

    std::cout << "Test passed: Insertion\n";
}

void testVectorAccess() {
    Vector<int> vec;

    // Test: Insert elements
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // Test: Access elements using at()
    assert(vec.at(0) == 10);
    assert(vec.at(1) == 20);
    assert(vec.at(2) == 30);

    // Test: Access elements using subscript operator []
    assert(vec[0] == 10);
    assert(vec[1] == 20);
    assert(vec[2] == 30);

    std::cout << "Test passed: Access\n";
}

void testVectorRemove() {
    Vector<int> vec;

    // Insert elements
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // Test: Remove an element at index
    vec.erase(1);  // Remove element at index 1 (value 20)

    // Test: Ensure the size decreases and the element is removed
    assert(vec.size() == 2);
    assert(vec.at(0) == 10);
    assert(vec.at(1) == 30);

    std::cout << "Test passed: Remove\n";
}

void testVectorSize() {
    Vector<int> vec;

    // Test: Initially the vector should be empty
    assert(vec.size() == 0);

    // Insert elements
    vec.push_back(10);
    vec.push_back(20);

    // Test: The size should now be 2
    assert(vec.size() == 2);

    // Insert another element
    vec.push_back(30);

    // Test: The size should now be 3
    assert(vec.size() == 3);

    std::cout << "Test passed: Size\n";
}

void testVectorSort() {
    Vector<int> vec;

    // Insert unsorted elements
    vec.push_back(30);
    vec.push_back(10);
    vec.push_back(20);

    // Test: Sort the vector
    vec.sort();

    // Test: Ensure the vector is sorted
    assert(vec.at(0) == 10);
    assert(vec.at(1) == 20);
    assert(vec.at(2) == 30);

    std::cout << "Test passed: Sort\n";
}

void testVectorEdgeCases() {
    Vector<int> vec;

    // Test: Insert a duplicate value
    vec.push_back(10);
    vec.push_back(10);

    // Test: Ensure the duplicate is inserted
    assert(vec.at(0) == 10);
    assert(vec.at(1) == 10);

    // Test: Insert empty vector and check size
    Vector<int> emptyVec;
    assert(emptyVec.size() == 0);

    // Test: Accessing an element in an empty vector should throw an exception
    bool caughtException = false;
    try {
        emptyVec.at(0);  // Should throw exception
    } catch (const std::out_of_range& e) {
        caughtException = true;
    }
    assert(caughtException);

    std::cout << "Test passed: Edge cases\n";
}

int main() {
    // Run all tests
    testVectorInsertion();
    testVectorAccess();
    testVectorRemove();
    testVectorSize();
    testVectorSort();
    testVectorEdgeCases();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}

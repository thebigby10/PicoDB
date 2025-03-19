#include <iostream>
#include <cassert>
#include "../include/PicoDB/Map.h"

void testMapInsertionAndRetrieval() {
    Map<int, std::string> map;

    // Test: Insert key-value pairs
    map.insert(1, "One");
    map.insert(2, "Two");
    map.insert(3, "Three");

    // Test: Retrieve values by keys
    assert(map.get(1) == "One");
    assert(map.get(2) == "Two");
    assert(map.get(3) == "Three");

    std::cout << "Test passed: Insertion and Retrieval\n";
}

void testMapRemove() {
    Map<int, std::string> map;

    // Insert some key-value pairs
    map.insert(1, "One");
    map.insert(2, "Two");

    // Test: Remove key-value pair
    map.remove(1);

    // Test: Ensure the removed key does not exist
    bool removed = false;
    try {
        map.get(1);  // Should throw exception or return some value indicating key not found
    } catch (const std::exception& e) {
        removed = true;
    }

    assert(removed);  // Key 1 should have been removed
    assert(map.size() == 1);  // The map should have only one element

    std::cout << "Test passed: Removal\n";
}

void testMapContains() {
    Map<int, std::string> map;

    // Insert key-value pairs
    map.insert(1, "One");
    map.insert(2, "Two");

    // Test: Check if a key exists
    assert(map.contains(1) == true);
    assert(map.contains(2) == true);
    assert(map.contains(3) == false);  // Key 3 should not be present

    std::cout << "Test passed: Contains check\n";
}

void testMapSize() {
    Map<int, std::string> map;

    // Test: Initially the map should be empty
    assert(map.size() == 0);

    // Insert elements
    map.insert(1, "One");
    map.insert(2, "Two");

    // Test: Size of the map after insertions
    assert(map.size() == 2);

    // Remove an element
    map.remove(1);

    // Test: Size after removal
    assert(map.size() == 1);

    std::cout << "Test passed: Size check\n";
}

void testMapEdgeCases() {
    Map<int, std::string> map;

    // Test: Inserting duplicate keys
    map.insert(1, "One");
    map.insert(1, "Duplicate");

    // Test: Ensure the value for key 1 is "Duplicate"
    assert(map.get(1) == "Duplicate");

    // Test: Inserting a key with empty string
    map.insert(2, "");

    // Test: Ensure the value for key 2 is ""
    assert(map.get(2) == "");

    std::cout << "Test passed: Edge cases\n";
}

int main() {
    // Run all tests
    testMapInsertionAndRetrieval();
    testMapRemove();
    testMapContains();
    testMapSize();
    testMapEdgeCases();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}

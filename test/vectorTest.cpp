#include <iostream>
#include "../src/Vector.cpp"

int main() {
    Vector<int> vec;

    // Push back elements
    vec.push_back(5);
    vec.push_back(10);
    vec.push_back(15);

    // Add element at a specific position
    vec.add(1, 7);  // Adding 7 at index 1

    // Print elements
    std::cout << "Vector elements after adding: ";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // Erase an element
    vec.erase(2);  // Remove element at index 2

    // Print elements after erase
    std::cout << "Vector elements after erasing: ";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;


    // Sort the vector
    vec.sort();

    std::cout << "Vector elements after sorting: ";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // Searching for an element
    int index = vec.search(10);
    if (index != -1) {
        std::cout << "Element 10 found at index: " << index << std::endl;
    } else {
        std::cout << "Element 10 not found" << std::endl;
    }


    // Swapping elements
    vec.swap(0, 1);
    std::cout << "Vector elements after swapping: ";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // Clearing the vector
    vec.clear();
    std::cout << "Vector size after clearing: " << vec.get_size() << std::endl;

    return 0;
}

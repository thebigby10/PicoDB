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

    return 0;
}

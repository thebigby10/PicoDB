#ifndef MAP_H // Include guard start
#define MAP_H

#include <iostream>
#include "Vector.cpp"
#include "String.cpp"

template <typename K, typename V>
class Map {
private:
    Vector<K> keys;
    Vector<V> values;

public:
    // Add a new key-value pair
    void insert(const K& key, const V& value) {
        // Check if key already exists
        for (size_t i = 0; i < keys.get_size(); ++i) {
            if (keys[i] == key) {
                values[i] = value; // Update the value if key exists
                return;
            }
        }
        // Add new key-value pair
        keys.push_back(key);
        values.push_back(value);
    }

    // Get the value for a given key
    V get(const K& key) const {
        for (size_t i = 0; i < keys.get_size(); ++i) {
            if (keys[i] == key) {
                return values[i];
            }
        }
        throw std::runtime_error("Key not found");
    }

    
};

#endif
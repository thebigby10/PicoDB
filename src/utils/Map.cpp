#include "../../include/PicoDB/Map.h"

// Add a new key-value pair
template<typename K, typename V>
void Map<K,V>::insert(const K& key, const V& value) {
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
template<typename K, typename V>
V Map<K,V>::get(const K& key) const {
    for (size_t i = 0; i < keys.get_size(); ++i) {
        if (keys[i] == key) {
            return values[i];
        }
    }
    throw std::runtime_error("Key not found");
}

// Remove a key-value pair
template<typename K, typename V>
void Map<K,V>::remove(const K& key) {
    for (size_t i = 0; i < keys.get_size(); ++i) {
        if (keys[i] == key) {
            keys.erase(keys.begin() + i);
            values.erase(values.begin() + i);
            return;
        }
    }
    throw std::runtime_error("Key not found");
}

// Check if a key exists in the map
template<typename K, typename V>
bool Map<K,V>::contains(const K& key) const {
    for (size_t i=0;i<keys.get_size();i++) {
        if (keys[i] == key) {
            return true;
        }
    }
    return false;
}

// Return the size of the map
template<typename K, typename V>
size_t Map<K,V>::size() const {
    return keys.get_size();
}

template<typename K, typename V>
Vector<K> Map<K,V>::get_keys() {
    return keys;
}

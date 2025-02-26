#ifndef MAP_H // Include guard start
#define MAP_H

#include "Vector.h"
#include "String.h"

template <typename K, typename V>
class Map {
private:
    Vector<K> keys;
    Vector<V> values;

public:
    // Add a new key-value pair
    void insert(const K& key, const V& value);

    // Get the value for a given key
    V get(const K& key) const ;

    // Remove a key-value pair
    void remove(const K& key) ;

    // Check if a key exists in the map
    bool contains(const K& key) const;

    // Return the size of the map
    size_t size() const;
    Vector<K> get_keys();
};

#endif

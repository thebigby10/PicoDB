#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <typename T>
class Vector {
    private:
        T* arr;          // Array to store the elements
        size_t size;     // Current number of elements
        size_t capacity; // Capacity of the array

        // Resizes the array when needed
        void resize() {
            capacity *= 2;
            T* newArr = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }

    public:
        // Constructor
        Vector(size_t initialCapacity = 2) : size(0), capacity(initialCapacity) {
            arr = new T[capacity];
        }

        // Constructor with initializer list
        Vector(std::initializer_list<T> list) : size(list.size()), capacity(list.size()) {
            arr = new T[capacity];
            size_t i = 0;
            for (const T& item : list) {
                arr[i++] = item;
            }
        }

        // Copy constructor
        Vector(const Vector& other) {
            size = other.size;
            capacity = other.capacity;
            arr = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                arr[i] = other.arr[i];
            }
        }

        // Destructor
        ~Vector() {
            delete[] arr;
        }
        Vector& operator =(const Vector& other);

        // Push back an element to the vector
        void push_back(const T& value);

        // Add an element at a specific index
        void add(size_t index, const T& value);

        // Erase an element at a specific index
        void erase(size_t index);

        // Sort the vector elements
        void sort();

        // Return the number of elements in the vector
        size_t get_size() const;

        // Search for an element in the vector, returns the index or -1 if not found
        int search(const T& value) const;

        // Access element at index
        T& at(size_t index);

        const T& at(size_t index) const ;

        // Swap two elements in the vector
        void swap(size_t i, size_t j) ;

        // Clear all elements in the vector
        void clear();

        // Delete the vector completely
        void deleteVector();

        // Overloading the subscript operator for easier access
        T& operator[](size_t index);

        const T& operator[](size_t index) const;

};

#endif

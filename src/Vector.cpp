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

        // Vector assignment operator
        Vector& operator =(const Vector& other) {
            if (this != &other) {
                delete[] arr;
                size = other.size;
                capacity = other.capacity;
                arr = new T[capacity];
                for (size_t i = 0; i < size; ++i) {
                    arr[i] = other.arr[i];
                }
            }
            return *this;
        }

        // Push back an element to the vector
        void push_back(const T& value) {
            if (size == capacity) {
                resize();
            }
            arr[size++] = value;
        }

        // Add an element at a specific index
        void add(size_t index, const T& value) {
            if (index > size) {
                throw std::out_of_range("Index out of range");
            }
            if (size == capacity) {
                resize();
            }
            for (size_t i = size; i > index; --i) {
                arr[i] = arr[i - 1];
            }
            arr[index] = value;
            ++size;
        }

        // Erase an element at a specific index
        void erase(size_t index) {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            for (size_t i = index; i < size - 1; ++i) {
                arr[i] = arr[i + 1];
            }
            --size;
        }
};

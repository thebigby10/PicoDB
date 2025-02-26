#include "../../include/PicoDB/Vector.h"

// Vector assignment operator
template<typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& other) {
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
template<typename T>
void Vector<T>::push_back(const T& value) {
    if (size == capacity) {
        resize();
    }
    arr[size++] = value;
}

// Add an element at a specific index
template<typename T>
void Vector<T>::add(size_t index, const T& value) {
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
template<typename T>
void Vector<T>::erase(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    --size;
}

// Sort the vector elements
template<typename T>
void Vector<T>::sort() {
    for (size_t i = 0; i < size - 1; ++i) {
            for (size_t j = 0; j < size - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    T temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
}

// Return the number of elements in the vector
template<typename T>
size_t Vector<T>::get_size() const {
    return size;
}

// Search for an element in the vector, returns the index or -1 if not found
template<typename T>
int Vector<T>::search(const T& value) const {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Access element at index
template<typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

// Swap two elements in the vector
template<typename T>
void Vector<T>::swap(size_t i, size_t j) {
    if (i >= size || j >= size) {
        throw std::out_of_range("Index out of range");
    }

    T temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Clear all elements in the vector
template<typename T>
void Vector<T>::clear() {
    size = 0;
}

// Delete the vector completely
template<typename T>
void Vector<T>::deleteVector() {
    delete[] arr;
    arr = nullptr;
    size = 0;
    capacity = 0;
}

// Overloading the subscript operator for easier access
template<typename T>
T& Vector<T>::operator[](size_t index) {
    return at(index); // Uses at() to handle index checking
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    return at(index);
}

#include<iostream>

template<typename T>
class Vector{
private:
	T* arr;
	size_t size;
	size_t capacity;

	Vector(const Vector& other) {
        size = other.size;
        capacity = other.capacity;
        arr = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            arr[i] = other.arr[i];
        }
    }
}
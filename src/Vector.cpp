#include<iostream>

template<typename T>
class Vector{
private:
	T* arr; //main vector array
	size_t size; //current number of element
	size_t capacity; //capacity of array

public:
	//constructor
	Vector(size_t initialCapacity = 2) : size(0), capacity(initialCapacity) {
        arr = new T[capacity];
    }
    //copy constructor
    Vector(const Vector& other) {
        size = other.size;
        capacity = other.capacity;
        arr = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            arr[i] = other.arr[i];
        }
    }
    //destructor
    ~Vector() {
        delete[] arr;
    }
}
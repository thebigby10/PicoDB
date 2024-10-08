#include<iostream>

template<typename T>
class Vector{
private:
	T* arr; //main vector array
	size_t size; //current number of element
	size_t capacity; //capacity of array

    //resizes the array for push_back
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
    //vector assignment
    Vector& operator=(const Vector& other) {
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
    //push back implementation
    void push_back(const T& value) {
        if (size == capacity) {
            resize();
        }
        arr[size++] = value;
    }
}
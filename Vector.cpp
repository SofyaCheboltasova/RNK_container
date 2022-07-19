#include "Vector.h"
#include <cstring>

Vector::Vector() {
    array = new int[1];
    capacity = 1;
    size = 0;
}

Vector::Vector(size_t size1, Nucl nucl) {
    array = new int[size1];

    for(size_t i = 0; i < size1; ++i) {
        array[i] = nucl;
    }
    capacity = size = size1;
}

int Vector::get(size_t i) const {
    return array[i];
}

void Vector::push_back(int elem) {
    if(size == capacity) {
        int* old_array = array;
        array = new int[capacity *= 2];

        for(size_t i = 0; i < size; ++i)
            array[i] = old_array[i];

        delete[] old_array;
    }
    array[size] = elem;
    ++size;
}

Vector Vector::copy_vector(const Vector& vector) {
    if (this->size >= vector.size) {
        for (size_t i = 0; i < size; ++i) {
            array[i] = vector.array[i];
        }
        this->size = vector.size;
        this->capacity = vector.capacity;
    }
    else {
        int* new_array = new int[vector.size];
        for(size_t i = 0; i < vector.size; ++i) {
            new_array[i] = vector.array[i];
        }
        delete[] array;
        array = new_array;
    }
    return *this;
}

void Vector::push(size_t index, const Nucl nucl) {
    array[index] = nucl;
}


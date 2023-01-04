#pragma once

#pragma once

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <utility>

template<class T> class DynamicArray
{
private:

    struct dynamicArray {
        size_t size;
        T* data;
    };

    dynamicArray array = { 0, nullptr };

public:

    // Создание объек

    DynamicArray(T* items, int count) {
        if (count < 0) throw std::runtime_error("Invalid array of size.");

        if (count == 0) return;

        array.data = new T[count];
        std::copy(items, items + count, array.data);
        array.size = count;
    };

    DynamicArray(int size) {
        if (size < 0) throw std::runtime_error("Invalid array of size.");

        if (size == 0) return;

        array.data = new T[size];
        array.size = size;
    };

    DynamicArray() : DynamicArray(0) {};

    DynamicArray(DynamicArray<T>& l) {
        array.data = new T[l.array.size];
        std::copy(l.array.data, l.array.data + l.array.size, array.data);
        array.size = l.array.size;
    };

    ~DynamicArray() {
        if (array.data != nullptr)
        {
            delete[] array.data;
        }
        array.size = 0;
    };

    // Декомпозиция

    T& operator[](size_t index) {
        if ((index < 0) || (index >= array.size)) throw std::runtime_error("Index out of range.");

        return array.data[index];
    };

    int GetSize() {
        return array.size;
    };

    T GetItem(size_t index) {
        if ((index < 0) || (index >= array.size)) throw std::runtime_error("Index out of range.");

        return array.data[index];
    };

    // Операции

    void Set(int index, T value) {
        if ((index < 0) || (index >= array.size)) throw std::runtime_error("Index out of range.");
        array.data[index] = value;
    };

    void Resize(size_t size) {
        if (size < 0) throw std::runtime_error("Invalid array of size.");

        T* copyData = array.data;
        array.data = new T[size];
        std::copy(copyData, copyData + std::min(array.size, size), array.data);
        array.size = size;

        delete[] copyData;
    };

    void PrintArray() {
        for (size_t i = 0; i < array.size; i++) std::cout << array.data[i] << ' ';
        std::cout << "\n";
    }

};

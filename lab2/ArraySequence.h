#pragma once

#include <cstddef>
#include <iostream>
#include "DynamicArray.h"
#include "ISortedSequence.h"

template <class T> class ArraySequence : public Sequence<T>
{
private:

    DynamicArray<T>* buffer;

    int Partition(DynamicArray<T>* buffer, int start, int end)
    {
        T divider = buffer->GetItem((start + end) / 2);
        int i = start, j = end;

        while (i <= j) {
            while (buffer->GetItem(i) > divider) {
                i++;
            }
            while (buffer->GetItem(j) < divider) {
                j--;
            }
            if (i >= j) break;
            T tmp = buffer->GetItem(i);
            buffer->Set(i, buffer->GetItem(j));
            buffer->Set(j, tmp);
            i++; j--;
        }

        return j;
    }

    void Sort(DynamicArray<T>* buffer, int start, int end) {
        if (start < end) {
            int divider = Partition(buffer, start, end);
            Sort(buffer, start, divider);
            Sort(buffer, divider + 1, end);
        }
    }

public:
    ArraySequence(T* items, size_t count) {
        buffer = new DynamicArray<T>(items, count);
        this->Sort(buffer, 0, buffer->GetSize() - 1);
    };

    ArraySequence() {
        buffer = new DynamicArray<T>();
    };

    ArraySequence(const ArraySequence<T>& list) {
        this->buffer = new DynamicArray<T>(list.GetLenght());
        for (int i = 0; i < list.GetLenght(); i++)
            this->buffer->Set(i, list.Get(i));
        this->Sort(buffer, 0, buffer->GetSize() - 1);
    };

    ~ArraySequence() {
        delete buffer;
    };

    T GetFirst() override {
        return this->buffer->GetItem(0);
    };

    T GetLast() override {
        return this->buffer->GetItem(this->GetLenght() - 1);
    };

    T Get(int index) const override {
        return this->buffer->GetItem(index);
    };

    T& operator[](size_t index) {
        return this->buffer->GetItem(index);
    };


    int GetLenght() const override {
        return this->buffer->GetSize();
    };

    void Print() override {
        this->buffer->PrintArray();
    }

    void Append(T item) override {
        this->buffer->Resize(this->GetLenght() + 1);
        this->buffer->Set(this->GetLenght() - 1, item);
        this->Sort(buffer, 0, buffer->GetSize() - 1);
    };

    void Prepend(T item) override {
        this->buffer->Resize(this->GetLenght() + 1);
        for (int i = this->GetLenght() - 1; i > 0; i--)
        {
            T tmp = this->Get(i);
            this->buffer->Set(i, this->Get(i - 1));
            this->buffer->Set(i - 1, tmp);
        }
        this->buffer->Set(0, item);
        this->Sort(buffer, 0, buffer->GetSize() - 1);
    };

    void InsertAt(T item, int index) override {
        this->buffer->Set(index, item);
        this->Sort(buffer, 0, buffer->GetSize() - 1);
    };
};



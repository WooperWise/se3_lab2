#pragma once

#include <iostream>

template <class T> class Sequence
{
public:

	virtual int GetLenght() const = 0;

	virtual T GetFirst() = 0;

	virtual T GetLast() = 0;

	virtual T Get(int index) const = 0;

	virtual void Append(T item) = 0;

	virtual void Prepend(T item) = 0;

	virtual void InsertAt(T item, int index) = 0;

	virtual void Print() = 0;

};

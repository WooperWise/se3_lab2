#pragma once

#include "ISortedSequence.h"

template <class T>
class BinSearch {
public:
    static bool Search(Sequence<T>* arr, T key)
    {
        int start = 0, end = arr->GetLenght(), mid = 0;
        while (start < end)
        {
            mid = (start + end) / 2;
            if (arr->Get(mid) < key)
                end = mid;
            else
                start = mid + 1;
        }
        end--;

        if (arr->Get(end) == key)
            return true;
        return false;
    }
};



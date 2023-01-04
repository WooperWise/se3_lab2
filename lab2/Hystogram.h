#pragma once

#include <map>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "ArraySequence.h"

using namespace std;

typedef struct Range
{
    int start;
    int end;
} Range;

typedef struct hstgrm
{
    ArraySequence<int> arr;
    Range range;
} hstgrm;

class Hystogram
{
private:
    vector<Range> range;
public:
    Hystogram();
    void CreateRange(int start, int end);
    void ClearRange();
    vector<hstgrm> CreateHystogram(ArraySequence<int>* arr);
};


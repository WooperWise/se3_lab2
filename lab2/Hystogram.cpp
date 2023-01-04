#include "Hystogram.h"

Hystogram::Hystogram() {};

void Hystogram::CreateRange(int start, int end)
{
	Range tmp = { start, end };
	range.push_back(tmp);
}

void Hystogram::ClearRange()
{
	if (range.empty()) return;
	else range.clear();
}

vector<hstgrm> Hystogram::CreateHystogram(ArraySequence<int>* arr)
{
	vector<hstgrm> res;
	for (auto k : range)
	{
		ArraySequence<int> tmp;
		for (int i = 0; i < arr->GetLenght(); i++)
		{
			if ((k.start <= arr->Get(i)) && (arr->Get(i) <= k.end))
				tmp.Append(arr->Get(i));
		}
		hstgrm pair;
		for (int i = 0; i < tmp.GetLenght(); i++)
		{
			pair.arr.Append(tmp.Get(i));
		}
		pair.range = k;
		res.push_back(pair);
	}
	return res;
}
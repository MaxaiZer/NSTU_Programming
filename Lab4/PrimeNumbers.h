#pragma once
#include <vector>

class PrimeNumbers
{
public:

	int FindLastLE(int digitToCompare)
	{
		for (int i = 1; i < numbers.size(); i++)
		{
			if (numbers[i] > digitToCompare)
				return numbers[i - 1];
		}
		return -1;
	}

	int FindFirstGE(int digitToCompare)
	{
		for (int i = 0; i < numbers.size(); i++)
		{
			if (numbers[i] >= digitToCompare)
				return numbers[i];
		}
		return -1;
	}

private:
	std::vector<int> numbers = { 1, 5, 7, 15, 31, 63, 127, 251,
		509, 1021, 2039, 4093, 8191,
		16381, 32749, 65521, 131071, 262139 };

};
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdexcept>
#include "task11.h"

using namespace Task11;

void findSubcolumnsSums(long long* matrix, long long* columnsSums, int rows, int columns, int subrows)
{
	for (int r = 0; r < rows - subrows + 1; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			long long  sum = 0;

			if (r > 0)
			{
				sum = columnsSums[(r - 1) * columns + c] + matrix[(r + subrows - 1) * columns + c] - matrix[(r - 1) * columns + c];
			}
			else
			{
				for (int curR = r; curR < r + subrows; curR++)
					sum += matrix[curR * columns + c];
			}

			columnsSums[r * columns + c] = sum;
		}
	}
}

Result findMaxSum(long long* columnsSums, int arrayRows, int arrayColumns, int subColumns)
{
	Result res = { LLONG_MIN, -1 };

	auto checkMaxSum = [&res, arrayColumns](long long sum, int curRow, int curColumn)
	{ 
		if (res.sum < sum)
		{
			res.sum = sum;
			res.firstElementId = curRow * arrayColumns + curColumn;
		}
	};

	for (int r = 0; r < arrayRows; r++)
	{
		long long  sum = 0;

		for (int c =  0; c < subColumns; c++)
			sum += columnsSums[arrayColumns * r + c];

		checkMaxSum(sum, r, 0);

		for (int c = subColumns; c < arrayColumns; c++)
		{
			sum -= columnsSums[arrayColumns * r + c - subColumns];
			sum += columnsSums[arrayColumns * r + c];

			checkMaxSum(sum, r, c - subColumns + 1);
		}
	}

	return res;
}

Result NoCuda::findSubmatrixWithMaxSum(long long* matrix, int rows, int columns, int subrows, int subcolumns)
{
	if (matrix == nullptr || subrows > rows || subcolumns > columns ||
		rows < 0 || columns < 0 || subrows < 0 || subcolumns < 0)
		throw std::invalid_argument::exception();

	unsigned int subcolumnsDim[2] = { (unsigned int)rows - subrows + 1 , (unsigned int)columns };
	long long* subcolumnsSums = (long long*)malloc(subcolumnsDim[0] * subcolumnsDim[1] * sizeof(long long));

	findSubcolumnsSums(matrix, subcolumnsSums, rows, columns, subrows);
	
	Result res = findMaxSum(subcolumnsSums, subcolumnsDim[0], subcolumnsDim[1], subcolumns);
	free(subcolumnsSums);
	return res;
}

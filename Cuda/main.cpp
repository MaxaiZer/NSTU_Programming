#include <stdio.h>
#include <fstream>
#include <limits.h>
#include <ctime> 
#include <stdexcept>
#include "task11.h"

struct ExecutionInfo
{
	Task11::Result res;
	float time; //sec
};

void generateMatrix(int** matrix, int rows, int columns, int min, int max)
{
	if (rows <= 0 || columns <= 0) throw std::invalid_argument::exception();

	srand(time(0));

	*matrix = (int*)malloc(rows * columns * sizeof(int));

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			(*matrix)[i * columns + j] = rand() % (max - min + 1) + min;
		}
	}
}

void readInfoFromFile(int& rows, int& columns, int& min, int& max, int& subrows, int& subcolumns)
{
	std::ifstream fin("info.txt");
	if (!fin) { printf("fail to open info.txt\n"); return; }

	fin >> rows >> columns >> min >> max >> subrows >> subcolumns;
	fin.close();
}

void writeResultsToFile(int* matrix, int rows, int columns, int subrows, int subcolumns, ExecutionInfo withCuda, ExecutionInfo withoutCuda)
{
	std::ofstream fout("result.txt");
	if (!fout) { printf("fail to open result.txt\n"); return; }

	auto writeSubmatrix = [&fout, matrix, rows, columns, subrows, subcolumns](Task11::Result res)
	{
		int startRow = res.firstElementId / columns;
		int startColumn = res.firstElementId % columns;

		for (int i = startRow; i < startRow + subrows; i++)
		{
			for (int j = startColumn; j < startColumn + subcolumns; j++)
				fout << matrix[i * columns + j] << " ";

			fout << "\n";
		}
	};

	fout << "The results are " << (withCuda.res == withoutCuda.res ? "" : "not ") << "equal\n";

	fout << "\nWith cuda:\n" << "Time: " << withCuda.time << "c\n"
		<< "Sum: " << withCuda.res.sum << "\n" << "Submatrix:\n";
	writeSubmatrix(withCuda.res);

	fout << "\nWithout cuda:\n" << "Time: " << withoutCuda.time << "c\n"
		<< "Sum: " << withoutCuda.res.sum << "\n" << "Submatrix:\n";
	writeSubmatrix(withoutCuda.res);

	fout.close();
}

int main(int argc, char** argv)
{
	int* matrix;

	int rows, columns, min, max, subrows, subcolumns;
	readInfoFromFile(rows, columns, min, max, subrows, subcolumns);

	generateMatrix(&matrix, rows, columns, min, max);

	auto execute = [matrix, rows, columns, subrows, subcolumns](Task11::Result(*func)(int*, int,int,int,int)) 
	{        
		ExecutionInfo info;
		struct timespec start, end;
		clock_gettime(CLOCK_REALTIME, &start);
		info.res = func(matrix, rows, columns, subrows, subcolumns);
		clock_gettime(CLOCK_REALTIME, &end);
		info.time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1.0 / 1000000000;
		return info;
	};

	ExecutionInfo info1 = execute(Task11::Cuda::findSubmatrixWithMaxSum);
	ExecutionInfo info2 = execute(Task11::NoCuda::findSubmatrixWithMaxSum);

	writeResultsToFile(matrix, rows, columns, subrows, subcolumns, info1, info2);
	return 0;
}

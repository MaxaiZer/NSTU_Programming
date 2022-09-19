#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "task11.h"
#include <device_functions.h>
#include <stdio.h>
#include <fstream>
#include <limits.h>
#include <ctime> 

int maxThreadsDim[3];

struct ExecutionInfo
{
	Task11::Result res;
	float time; //sec
};

__global__ void findSubcolumnSum(int* matrix, int* columnsSums, int rows, int columns, int subrows)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	int row = i / columns;
	int column = i % columns;

	if (row >= rows || column >= columns) return;

	int sum = 0;

	for (int curRow = row; curRow < row + subrows; curRow++)
	{
		sum += matrix[columns * curRow + column];
	}

	columnsSums[columns * row + column] = sum;
}

__device__ int maxSum = INT_MIN;
__device__ int submatrixFirstElementId;

__global__ void findMaxSubcolumnSum(int* columnsSums, int arrayRows, int arrayColumns, int subColumns)
{
	int row = blockDim.x * blockIdx.x + threadIdx.x;
	if (row >= arrayRows) return;

	int threadMaxSum = 0, sum = 0, firstElementId = row * arrayColumns;

	for (int i = 0; i < subColumns; i++)
	{
		sum += columnsSums[arrayColumns * row + i];
	}

	threadMaxSum = sum;

	for (int i = 0; i < arrayColumns - subColumns; i++)
	{
		sum -= columnsSums[arrayColumns * row + i];
		sum += columnsSums[arrayColumns * row + i + subColumns];

		if (threadMaxSum < sum)
		{
			threadMaxSum = sum;
			firstElementId = row * arrayColumns + i + 1;
		}
	}

	atomicMax(&maxSum, threadMaxSum);
	__syncthreads();

	if (maxSum == threadMaxSum)
		atomicExch(&submatrixFirstElementId, firstElementId);
}

void getNumberOfBlocksAndThreads(int elemsCount, int* blocks, int* threads)
{
	*blocks = (elemsCount - 1) / maxThreadsDim[0] + 1;
	*threads = (elemsCount < maxThreadsDim[0] ? elemsCount : maxThreadsDim[0]);
}

cudaError_t allocateMemory(int* matrix, int** gpuMatrix, int rows, int columns, int** gpuColumnsSums, int subRows)
{
	cudaError_t status = cudaMalloc(gpuMatrix, rows * columns * sizeof(int));
	status = cudaMemcpy(*gpuMatrix, matrix, rows * columns * sizeof(int), cudaMemcpyHostToDevice);
	status = cudaMalloc(gpuColumnsSums, (rows - subRows + 1) * columns * sizeof(int));
	return status;
}

Task11::Result findSubmatrixWithMaxSumCuda(int* matrix, int rows, int columns, int subrows, int subcolumns)
{
	if (matrix == nullptr || subrows > rows || subcolumns > columns ||
		rows < 0 || columns < 0 || subrows < 0 || subcolumns < 0)
		throw std::invalid_argument::exception();

	cudaDeviceProp deviceProp;
	cudaGetDeviceProperties(&deviceProp, 0);
	memcpy(maxThreadsDim, deviceProp.maxThreadsDim, 3 * sizeof(int));

	int* _matrix = nullptr, *subcolumnsSums = nullptr;
	dim3 subcolumnsDim = { (unsigned int)rows - subrows + 1 , (unsigned int)columns };

	if (allocateMemory(matrix, &_matrix, rows, columns, &subcolumnsSums, subrows) != cudaSuccess)
	{
		printf("Allocate memory error!\n");
		return { -1,-1 };
	}

	int blocks, threads;
	getNumberOfBlocksAndThreads(subcolumnsDim.x * subcolumnsDim.y, &blocks, &threads);

	findSubcolumnSum << < blocks, threads >> > (_matrix, subcolumnsSums, rows, columns, subrows);
	cudaDeviceSynchronize();

	getNumberOfBlocksAndThreads(subcolumnsDim.x, &blocks, &threads);

	findMaxSubcolumnSum << < blocks, threads >> > (subcolumnsSums, subcolumnsDim.x, subcolumnsDim.y, subcolumns);
	cudaDeviceSynchronize();

	Task11::Result res;
	cudaMemcpyFromSymbol(&res, maxSum, sizeof(int));
	cudaMemcpyFromSymbol(&res.firstElementId, submatrixFirstElementId, sizeof(int));

	cudaFree(_matrix);
	cudaFree(subcolumnsSums);
	return res;
}

void generateMatrix(int** matrix, int rows, int columns, int min, int max)
{
	if (rows <= 0 || columns <= 0) throw std::invalid_argument::exception();

	srand(time(0));

	*matrix = (int*)malloc(rows * columns * sizeof(int));

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			(*matrix)[i * columns + j] = rand () % (max - min + 1) + min;
		}
	}
}

void readInfoFromFile(int& rows, int& columns, int& min, int& max, int& subrows, int& subcolumns)
{
	std::ifstream fin("info.txt");
	if (!fin) return;

	fin >> rows >> columns >> min >> max >> subrows >> subcolumns;
	fin.close();
}

/*
void readMatrixFromFile(int** matrix, int& rows, int& columns)
{
	std::ifstream fin("matrix.txt");
	if (!fin) return;

	fin >> rows >> columns;
	*matrix = (int*)malloc(rows * columns * sizeof(int));

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			fin >> (*matrix)[i * columns + j];
		}
	}

	fin.close();
}
*/

void writeResultsToFile(int* matrix, int rows, int columns, int subrows, int subcolumns, ExecutionInfo withCuda, ExecutionInfo withoutCuda)
{
	std::ofstream fout("result.txt");
	if (!fout) return;

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

	//readMatrixFromFile(&matrix, rows, columns);
	generateMatrix(&matrix, rows, columns, min, max);

	ExecutionInfo info1, info2;
	struct timespec start, end;

	clock_gettime(CLOCK_REALTIME, &start);
	//unsigned int start_time = clock();
	info1.res = findSubmatrixWithMaxSumCuda(matrix, rows, columns, subrows, subcolumns);
	//unsigned int end_time = clock();
	//info1.time = (float)(end_time - start_time) / CLOCKS_PER_SEC;
	clock_gettime(CLOCK_REALTIME, &end);
	info1.time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1.0 / 1000000000;


	clock_gettime(CLOCK_REALTIME, &start);
	//start_time = clock();
	info2.res = Task11::findSubmatrixWithMaxSum(matrix, rows, columns, subrows, subcolumns);
	//end_time = clock();
	//info2.time = (float)(end_time - start_time) / CLOCKS_PER_SEC;
	clock_gettime(CLOCK_REALTIME, &end);
	info2.time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1.0 / 1000000000;

	writeResultsToFile(matrix, rows, columns, subrows, subcolumns, info1, info2);
	return 0;
}
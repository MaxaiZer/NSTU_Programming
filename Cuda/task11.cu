#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <device_functions.h>
#include <stdexcept>
#include "task11.h"

using namespace Task11;

int maxThreadsDim[3];

__global__ void findSubcolumnSum(long long* matrix, long long* columnsSums, int rows, int columns, int subrows)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	int column = i % columns;

	if (column >= columns) return;

	int sum = 0;

	for (int curRow = 0; curRow < subrows; curRow++)
	{
		sum += matrix[columns * curRow + column];
	}
	columnsSums[column] = sum;

	for (int curRow = subrows; curRow < rows; curRow++)
	{
		sum -= matrix[columns * (curRow - subrows) + column];
		sum += matrix[columns * curRow + column];

		columnsSums[columns * (curRow - subrows + 1) + column] = sum;
	}
}

__device__ long long maxSum = INT_MIN;
__device__ int submatrixFirstElementId;

__global__ void findMaxSumOfSubcolumns(long long* columnsSums, int arrayRows, int arrayColumns, int subColumns)
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

cudaError_t allocateMemory(long long* matrix, long long** gpuMatrix, int rows, int columns, long long** gpuColumnsSums, int subRows)
{
	cudaError_t status = cudaMalloc(gpuMatrix, rows * columns * sizeof(long long));
	status = cudaMemcpy(*gpuMatrix, matrix, rows * columns * sizeof(long long), cudaMemcpyHostToDevice);
	status = cudaMalloc(gpuColumnsSums, (rows - subRows + 1) * columns * sizeof(long long));
	return status;
}

Result Cuda::findSubmatrixWithMaxSum(long long* matrix, int rows, int columns, int subrows, int subcolumns)
{
	if (matrix == nullptr || subrows > rows || subcolumns > columns ||
		rows < 0 || columns < 0 || subrows < 0 || subcolumns < 0)
		throw std::invalid_argument::exception();

	cudaDeviceProp deviceProp;
	cudaGetDeviceProperties(&deviceProp, 0);
	memcpy(maxThreadsDim, deviceProp.maxThreadsDim, 3 * sizeof(int));

	long long* _matrix = nullptr, * subcolumnsSums = nullptr;
	dim3 subcolumnsDim = { (unsigned int)rows - subrows + 1 , (unsigned int)columns };

	if (allocateMemory(matrix, &_matrix, rows, columns, &subcolumnsSums, subrows) != cudaSuccess)
	{
		printf("Allocate memory error!\n");
		return { -1,-1 };
	}

	int blocks, threads;

	getNumberOfBlocksAndThreads(subcolumnsDim.y, &blocks, &threads);
	findSubcolumnSum << <blocks, threads >> > (_matrix, subcolumnsSums, rows, columns, subrows);

	cudaDeviceSynchronize();

	getNumberOfBlocksAndThreads(subcolumnsDim.x, &blocks, &threads);
	findMaxSumOfSubcolumns << < blocks, threads >> > (subcolumnsSums, subcolumnsDim.x, subcolumnsDim.y, subcolumns);

	cudaDeviceSynchronize();

	Task11::Result res;
	cudaMemcpyFromSymbol(&res, maxSum, sizeof(long long));
	cudaMemcpyFromSymbol(&res.firstElementId, submatrixFirstElementId, sizeof(int));

	cudaFree(_matrix);
	cudaFree(subcolumnsSums);
	return res;
}
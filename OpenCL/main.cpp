#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <fstream>
#include <string.h>
#include <CL/cl.h>

#define PROGRAM_FILE "kernel.cl"
#define KERNEL_FUNC "calculateLengths"
#define OUTPUT_FILE "result.txt"

struct OpenCLProgramBuilder
{
	struct Info
	{
		cl_program program = NULL;
		cl_context context = NULL;
		cl_command_queue queue = NULL;
		cl_device_id device_id;
		cl_platform_id cpPlatform;

		cl_int error;
	};
	
	void Build(const char** sourceCode, Info& info)
	{
		info.error = clGetPlatformIDs(1, &info.cpPlatform, NULL);
		info.error = clGetDeviceIDs(info.cpPlatform, CL_DEVICE_TYPE_GPU, 1, &info.device_id, NULL);
		info.context = clCreateContext(0, 1, &info.device_id, NULL, NULL, &info.error);
		info.queue = clCreateCommandQueue(info.context, info.device_id, 0, &info.error);
		info.program = clCreateProgramWithSource(info.context, 1, sourceCode, NULL, &info.error);
		info.error = clBuildProgram(info.program, 0, NULL, NULL, NULL, NULL);
	}
	
	void Dispose(Info& info)
	{
		if (info.program != NULL) clReleaseProgram(info.program);		
		if (info.queue != NULL) clReleaseCommandQueue(info.queue);
		if (info.context != NULL) clReleaseContext(info.context);
	}
};

void readFile(char* name, char** buffer)
{
	std::ifstream fin(name);
	std::string content((std::istreambuf_iterator<char>(fin)),
		(std::istreambuf_iterator<char>()));

	*buffer = (char*)calloc(content.length() + 1, sizeof(char));
	strcpy(*buffer, content.data());
}

void writeResultsToFile(int firstNumber, int* resWithOpenCL, int* resWithoutOpenCL, float timeWithOpenCL, float timeWithoutOpenCL, unsigned int size)
{
	std::ofstream fout(OUTPUT_FILE);

	bool resultsEqual = true;
	for (int i = 0; i < size; i++)
	{
		if (resWithoutOpenCL[i] != resWithOpenCL[i]) { resultsEqual = false; break; }
	}

	fout << "The results are " << (resultsEqual ? "" : "not ") << "equal\n";
	fout << "With OpenCL | without OpenCL\nTime: " << timeWithOpenCL << "c | " << timeWithoutOpenCL << "c\n";
	fout << "Number: length#1 | length#2\n";

	for (int i = 0; i < size; i++)
	{
		fout << firstNumber + i << " : " << resWithOpenCL[i] << " | " << resWithoutOpenCL[i] << "\n";
	}

	fout.close();
}

void calculateWithOpenCL(int firstNumber, int* lengths, unsigned int size)
{
	char* sourceCode;
	readFile(PROGRAM_FILE, &sourceCode);
	
	OpenCLProgramBuilder::Info info;
	OpenCLProgramBuilder program;
	program.Build((const char**)&sourceCode, info);
	
	if (info.error != CL_SUCCESS) { printf("Build program error %d\n", info.error); return; };

	size_t localSize = 64;
	size_t globalSize = ceil((float)size /localSize) * localSize;
        
        cl_int error;       
	cl_kernel kernel = clCreateKernel(info.program, KERNEL_FUNC, &error);

	cl_mem d_lengths = clCreateBuffer(info.context, CL_MEM_READ_ONLY, size * sizeof(int), NULL, NULL);

	error |= clSetKernelArg(kernel, 0, sizeof(int), &firstNumber);
	error |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_lengths);
	error |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &size);
	error |= clEnqueueNDRangeKernel(info.queue, kernel, 1, NULL, &globalSize, &localSize,
		0, NULL, NULL);

	clFinish(info.queue);

	if (error != CL_SUCCESS) { printf("Execute kernel error!\n", error); return; };

	clEnqueueReadBuffer(info.queue, d_lengths, CL_TRUE, 0,
		size * sizeof(int), lengths, 0, NULL, NULL);
	
	clReleaseKernel(kernel);
	clReleaseMemObject(d_lengths);
	program.Dispose(info);
	free(sourceCode);
}

void calculateWithoutOpenCL(int firstNumber, int* lengths, unsigned int size)
{
	for (int i = 0; i < size; i++)
	{
		unsigned int n = firstNumber + i;
		int length = 1;

		while (n != 1)
		{
			n = (n % 2 == 0 ? n / 2 : 3 * n + 1);
			length++;
		}

		lengths[i] = length;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3) { printf("Required args: number#1, number#2\n"); return -1; }

	long firstNumber = strtol(argv[1], NULL, 10);
	long secondNumber = strtol(argv[2], NULL, 10);

	if (firstNumber > secondNumber || firstNumber <= 1 || secondNumber <= 1) { printf("Condition: number#2 > number#1 > 1\n"); return -1; }

	unsigned int arraySize = secondNumber - firstNumber + 1;

	int* lengths1 = (int*)malloc(arraySize * sizeof(int));
	int* lengths2 = (int*)malloc(arraySize * sizeof(int));

	auto execute = [firstNumber, arraySize](void(*func)(int, int*, unsigned int), int* lengths)
	{
		struct timespec start, end;
		clock_gettime(CLOCK_REALTIME, &start);
		func(firstNumber, lengths, arraySize);
		clock_gettime(CLOCK_REALTIME, &end);
		return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1.0 / 1000000000;
	};

	printf("Calculation with OpenCL...\n");
	float time1 = execute(calculateWithOpenCL, lengths1);

	printf("Calculation without OpenCL...\n");
	float time2 = execute(calculateWithoutOpenCL, lengths2);

	printf("Writing results to file...\n");
	writeResultsToFile(firstNumber, lengths1, lengths2, time1, time2, arraySize);

	free(lengths1);
	free(lengths2);
	return 0;
}

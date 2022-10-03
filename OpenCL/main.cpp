#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <fstream>
#include <string>
#include <CL/cl.h>

#define PROGRAM_FILE "kernel.cl"
#define KERNEL_FUNC "calculateLengths"
#define OUTPUT_FILE "result.txt"

struct OpenCLProgramBuilder
{
	cl_platform_id cpPlatform;        
	cl_device_id device_id;           
	cl_context context = NULL;               
	cl_command_queue queue = NULL;           
	cl_program program = NULL;              

	size_t globalSize, localSize;

	cl_int error;

	OpenCLProgramBuilder(const char** sourceCode)
	{
		error = clGetPlatformIDs(1, &cpPlatform, NULL);
		error = clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
		context = clCreateContext(0, 1, &device_id, NULL, NULL, &error);
		queue = clCreateCommandQueue(context, device_id, 0, &error);
		program = clCreateProgramWithSource(context, 1, sourceCode, NULL, &error);
		error = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	}

	~OpenCLProgramBuilder()
	{
		if (program != NULL) clReleaseProgram(program);		
		if (queue != NULL) clReleaseCommandQueue(queue);
		if (context != NULL) clReleaseContext(context);
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
	
	OpenCLProgramBuilder cl((const char**)&sourceCode);
	
	if (cl.error != CL_SUCCESS) { printf("Setup OpenCL error %d\n", cl.error); return; };

	cl.localSize = 64;
	cl.globalSize = ceil((float)size / cl.localSize) * cl.localSize;

	cl_kernel kernel = clCreateKernel(cl.program, KERNEL_FUNC, &cl.error);

	cl_mem d_lengths = clCreateBuffer(cl.context, CL_MEM_READ_ONLY, size * sizeof(int), NULL, NULL);

	cl_int err = clSetKernelArg(kernel, 0, sizeof(int), &firstNumber);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_lengths);
	err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &size);
	err = clEnqueueNDRangeKernel(cl.queue, kernel, 1, NULL, &cl.globalSize, &cl.localSize,
		0, NULL, NULL);

	clFinish(cl.queue);

	if (err != CL_SUCCESS) { printf("Error %d\n", err); return; };

	clEnqueueReadBuffer(cl.queue, d_lengths, CL_TRUE, 0,
		size * sizeof(int), lengths, 0, NULL, NULL);
	
	clReleaseKernel(kernel);
	clReleaseMemObject(d_lengths);
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
			//if (firstNumber + i == 113383) printf("%ld\n", n);
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
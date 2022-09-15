#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>
#include <string.h>

bool isParallel = true;

int* getPrimeNumbers(long long maxNumber, int *count)
{
    if (maxNumber < 2)
        return NULL;

    int arraySize = 50;
    int* primeNumbers = malloc(sizeof(int) * arraySize);

    primeNumbers[0] = 2;
    int curCount = 1;

    for (long long n = 3; n < maxNumber; n += 2)
    {
        bool isPrime = true;

        for (int i = 1; i < curCount; i++)
        {
            if (n % primeNumbers[i] == 0)
            {
                isPrime = false;
                break;
            }
        }

        if (!isPrime)
            continue;

        if (curCount == arraySize)
        {
            arraySize *= 2;
            primeNumbers = realloc(primeNumbers, sizeof(int) * arraySize); 
        }

        primeNumbers[curCount++] = n;
    }

    primeNumbers = realloc(primeNumbers, sizeof(int) * curCount);
    *count = curCount;
    return primeNumbers;
}

typedef struct
{
    int number;
    int primeNumbers[4];
} Result;

Result solveTask(long long number)
{
    int primeNumbersCount;
    int* primeNumbers = getPrimeNumbers((number < 287 ? 8 : sqrt(number)), &primeNumbersCount);

    Result result = {INT_MAX, {-1, -1, -1, -1}};

    #pragma omp parallel for collapse(3) if (isParallel) shared(number, primeNumbersCount, primeNumbers)
    for (int i = 0; i < primeNumbersCount; i++)
    {
        for (int j = 0; j < primeNumbersCount; j++)
        {
            for (int k = 0; k < primeNumbersCount; k++)
            {
                Result threadResult = {INT_MAX, {-1, -1, -1, -1}};
                bool skipCycle = false;

                for (int s = 0; s < primeNumbersCount; s++)
                {
                    if (skipCycle || i == j || i == k || i == s || j == k || j == s || k == s)
                        continue;

                    int sum = pow(primeNumbers[i], 2) + pow(primeNumbers[j], 3) +
                              pow(primeNumbers[k], 4) + pow(primeNumbers[s], 5);

                    if (sum <= number)
                        continue;

                    if (sum < threadResult.number)
                    {
                        Result _result =
                            {
                                sum,
                                {primeNumbers[i], primeNumbers[j],
                                 primeNumbers[k], primeNumbers[s]}
                            };
                        threadResult = _result;
                    }
                    else
                        skipCycle = true;
                }

                #pragma omp critical
                if (threadResult.number < result.number)
                {
                    result = threadResult;
                }
            }
        }
    }

    free(primeNumbers);
    return result;
}

Result solveTaskWithPrintingInfo(long long number)
{
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    Result res = solveTask(number);

    clock_gettime(CLOCK_REALTIME, &end);

    printf("%d = %d^2 + %d^3 + %d^4 + %d^5\n", res.number, res.primeNumbers[0], res.primeNumbers[1], res.primeNumbers[2], res.primeNumbers[3]);
    printf("time: %.6f sec\n", (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1.0 / 1000000000);
    return res;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("required argument: number\n");
        return -1;
    }

    long long number = strtol(argv[1], NULL, 10);
    
    printf("Parallel calculation:\n");
    Result res1 = solveTaskWithPrintingInfo(number);
    
    isParallel = false;
    printf("\nNot parallel calculation:\n");
    Result res2 = solveTaskWithPrintingInfo(number);
    
    if (res1.number == res2.number && 
    memcmp(res1.primeNumbers, res2.primeNumbers, sizeof(res1.primeNumbers)) == 0)
        printf("\nThe results are equal\n");
    else
        printf("\nThe results are not equal\n");
        
    return 0;
}

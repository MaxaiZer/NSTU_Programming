#include <mpi.h>
#include <math.h>
#include <limits.h>
#include <omp.h>
#include <vector>
#include <iostream>

using namespace std;

void getPrimeNumbers(long long maxNumber, vector<int>& primes)
{
    primes.push_back(2);

    for (long long n = 3; n < maxNumber; n += 2)
    {
        bool isPrime = true;

        for (unsigned int i = 1; i < primes.size(); i++)
        {
            if (n % primes[i] == 0) { isPrime = false; break; }
        }

        if (isPrime)
            primes.push_back(n);
    }
}

struct Result
{
    long long number;
    int primeNumbers[3];
    bool operator == (Result res) { return number == res.number;  }
};

void calculateResultForCyclePart(int iStart, int iEnd, long long number, const vector<int>& primes, Result& result)
{
    for (int i = iStart; i >= iEnd; i--)
    {
        for (int j = primes.size() - 1; j >= 0; j--)
        {
            for (int k = primes.size() - 1; k >= 0; k--)
            {
                if (i == j || i == k || j == k)
                    continue;

                long long sum = pow(primes[i], 2) + pow(primes[j], 3) + pow(primes[k], 4);
                
                if (sum >= number)
                    continue;

                if (sum > result.number)
                {
                    Result _result = {sum, {primes[i], primes[j], primes[k]}};
                    result = _result;
                }
                else
                    break;
            }
        }
    }  
}

void calculateParallel(long long number, const vector<int> &primes, int processCount, int processRank, Result &res)
{
    int elementsPerProcess = primes.size() / processCount;
    int start = processRank * elementsPerProcess;
    int end = (processRank == processCount - 1 ? primes.size() - 1 : start + elementsPerProcess);

    res = {INT_MIN, {-1, -1, -1}};
    calculateResultForCyclePart(end, start, number, primes, res);
}

void sendVectorToOtherProcesses(int thisProcessRank, int processCount, const vector<int> &v)
{
    for (int i = 0; i < processCount; i++)
    {
        if (i == thisProcessRank)
            continue;
        unsigned int size = v.size();
        MPI_Send(&size, 1, MPI_UNSIGNED, i, 0, MPI_COMM_WORLD);
        MPI_Send(&v.front(), v.size(), MPI_INT, i, 0, MPI_COMM_WORLD);
    }
}

void receiveVector(int anotherProcessRank, vector<int> &v)
{
    unsigned int size;
    MPI_Recv(&size, 1, MPI_UNSIGNED, anotherProcessRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    v.resize(size);

    MPI_Recv(&v.front(), size, MPI_INT, anotherProcessRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void printExecutionInfo(Result res, struct timespec start, struct timespec end)
{
    if (res.number < 0)
        printf("No result\n");
    else
        printf("%lld = %d^2 + %d^3 + %d^4\n", res.number, res.primeNumbers[0], res.primeNumbers[1], res.primeNumbers[2]);
            
    printf("time: %.6f sec\n\n", (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1.0 / 1000000000);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("required argument: number\n");
        return -1;
    }

    MPI_Init(NULL, NULL);

    long long number = strtol(argv[1], NULL, 10);

    int processCount, processRank;
    
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
    
    struct timespec start, end;
    
    //NOT PARALLEL CALCULATION
    Result res1 = {INT_MIN, {-1, -1, -1}};
    if (processRank == 0)
    {
        printf("Not parallel calculation:\n");      
        clock_gettime(CLOCK_REALTIME, &start);
        
        vector<int> primes;
        getPrimeNumbers((number < 287 ? 8 : sqrt(number)), primes);
        
        calculateResultForCyclePart(primes.size() - 1, 0, number, primes, res1);
        
        clock_gettime(CLOCK_REALTIME, &end);       
        printExecutionInfo(res1, start, end);
    }
    
    //PARALLEL CALCULATION
    vector<int> primes;

    if (processRank == 0)
    {
        printf("Parallel calculation:\n");
        clock_gettime(CLOCK_REALTIME, &start);

        getPrimeNumbers((number < 287 ? 8 : sqrt(number)), primes);
        sendVectorToOtherProcesses(processRank, processCount, primes);
    }
    else
    {
        receiveVector(0, primes);
    }

    Result res2 = {INT_MIN, {-1, -1, -1}};
    calculateParallel(number, primes, processCount, processRank, res2);
    
    if (processRank != 0) //sending result to process #0
    {
        MPI_Send(&res2, sizeof(Result) / sizeof(int), MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    if (processRank == 0)
    {
        for (int i = 1; i < processCount; i++)
        {
            Result threadResult;
            MPI_Recv(&threadResult, sizeof(Result) / sizeof(int), MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            if (res2.number < threadResult.number)
                res2 = threadResult;
        }    
        
        clock_gettime(CLOCK_REALTIME, &end);       
        printExecutionInfo(res2, start, end);
        
        std::cout << "The results are " << (res1 == res2 ? "" : "not ") << "equal\n";
    }
    
    MPI_Finalize(); 
    return 0;
}

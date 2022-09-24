namespace Task11
{
    struct Result
    {
        long long sum;
        int firstElementId;
        bool operator==(Result res) { return sum == res.sum; }
    };

    namespace Cuda
    {
        Result findSubmatrixWithMaxSum(long long* matrix, int rows, int columns, int subrows, int subcolumns);
    }
    namespace NoCuda
    {
        Result findSubmatrixWithMaxSum(long long* matrix, int rows, int columns, int subrows, int subcolumns);
    }
}
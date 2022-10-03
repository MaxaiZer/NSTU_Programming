namespace Task11
{
    struct Result
    {
        int sum;
        int firstElementId;
        bool operator==(Result res) { return sum == res.sum; }
    };

    namespace Cuda
    {
        Result findSubmatrixWithMaxSum(int* matrix, int rows, int columns, int subrows, int subcolumns);
    }
    namespace NoCuda
    {
        Result findSubmatrixWithMaxSum(int* matrix, int rows, int columns, int subrows, int subcolumns);
    }
}

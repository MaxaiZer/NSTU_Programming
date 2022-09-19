namespace Task11
{
    struct Result
    {
        int sum;
        int firstElementId;
        bool operator==(Result res) { return sum == res.sum; }
    };

    void findSubcolumnSum(int* matrix, int* columnsSums, int rows, int columns, int subrows);
    Result findMaxSubcolumnSum(int* columnsSums, int arrayRows, int arrayColumns, int subColumns);
    Result findSubmatrixWithMaxSum(int* matrix, int rows, int columns, int subrows, int subcolumns); 
}
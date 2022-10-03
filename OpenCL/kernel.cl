__kernel void calculateLengths(int startNumber,
    __global int* lengths,
    const unsigned int arraySize)
{                              
    int id = get_global_id(0);
    if (id >= arraySize) return;

    unsigned int n = startNumber + id;
    int length = 1;
    
    while (n != 1)
    {
        n = (n % 2 == 0 ? n / 2 : 3 * n + 1);
        length++;
    }
    
    lengths[id] = length;
}
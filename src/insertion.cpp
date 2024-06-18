#include <iostream>

namespace sorting
{
    void insertion(int *array, int n, bool reverse)
    {
        int i = 1;

        while (i < n)
        {
            int key = array[i];
            int j = i - 1;

            while (j >= 0 && (reverse ? array[j] > key : array[j] < key))
            {
                array[j + 1] = array[j];
                j--;
            }

            array[j + 1] = key;
            i++;
        }
    }
}

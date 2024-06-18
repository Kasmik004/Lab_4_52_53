#include <iostream>

void quick(int *array, int n, bool reverse)
{
    if (n <= 1)
    {
        return;
    }

    int pivot = array[n / 2];
    int i = 0;
    int j = n - 1;

    while (i <= j)
    {
        if (reverse)
        {
            while (array[i] > pivot)
            {
                i++;
            }

            while (array[j] < pivot)
            {
                j--;
            }
        }
        else
        {
            while (array[i] < pivot)
            {
                i++;
            }

            while (array[j] > pivot)
            {
                j--;
            }
        }

        if (i <= j)
        {
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    quick(array, j + 1, reverse);
    quick(array + i, n - i, reverse);
}

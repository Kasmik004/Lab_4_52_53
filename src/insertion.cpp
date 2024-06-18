#include <iostream>
#include "sorting.h"

#include <random>
#include <chrono>
#include <string>

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

namespace measurement
{
    enum class MeasureType
    {
        BestCase,
        WorstCase,
        AverageCase
    };

    // Refs:
    // std::chrono::duration_cast https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
    // std::chrono::high_resolution_clock https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
    template <typename T>
    long long time_since_epoch()
    {
        return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }
}

long long get_avg_sort_time(int *array, int n, int num_trials = 3, measurement::MeasureType type = measurement::MeasureType::AverageCase)
{
    long long total_time = 0;

    if (type == measurement::MeasureType::BestCase)
    {
        sorting::insertion(array, n, false);
    }
    else if (type == measurement::MeasureType::WorstCase)
    {
        sorting::insertion(array, n, true);
    }

    for (int i = 0; i < num_trials; i++)
    {
        int *copy = new int[n];
        std::copy(array, array + n, copy);

        long long t = measurement::time_since_epoch<std::chrono::nanoseconds>();
        sorting::insertion(copy, n, false);
        total_time += measurement::time_since_epoch<std::chrono::nanoseconds>() - t;

        delete[] copy;
    }

    return total_time / num_trials;
}

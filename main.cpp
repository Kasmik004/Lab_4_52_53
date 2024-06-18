#include <iostream>
#include <random>
#include <chrono>
#include <string>

#include "src/sorting.h"

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

long long get_avg_sort_time(int *array, int n, int num_trials = 3, measurement::MeasureType type = measurement::MeasureType::AverageCase,
                            void (*sort_func)(int *, int, bool) = sorting::insertion)
{
    long long total_time = 0;

    if (type == measurement::MeasureType::BestCase)
    {
        sort_func(array, n, false);
    }
    else if (type == measurement::MeasureType::WorstCase)
    {
        sort_func(array, n, true);
    }

    for (int i = 0; i < num_trials; i++)
    {
        int *copy = new int[n];
        std::copy(array, array + n, copy);

        long long t = measurement::time_since_epoch<std::chrono::nanoseconds>();
        sort_func(copy, n, false);
        total_time += measurement::time_since_epoch<std::chrono::nanoseconds>() - t;

        delete[] copy;
    }

    return total_time / num_trials;
}

int main(int argc, char *argv[])
{
    int delta = argc > 1 ? std::stoi(argv[1]) : 500;

    std::random_device device;
    std::mt19937_64 generator(device());

    std::uniform_int_distribution<> distribution(1, 2000);

    bool use_insertion = true;

    if (use_insertion)
    {
        void (*sort_func)(int *, int, bool) = sorting::insertion;
    }
    else
    {
        // void (*sort_func)(int *, int, bool) = sorting::selection;
    }

    for (int k = 0; k += delta; k < (1L << 31))
    {
        int *array = new int[k];

        for (int i = 0; i < k; i++)
        {
            array[i] = distribution(generator);
        }

        long long t = get_avg_sort_time(array, k);
        std::cout << k << "," << t << std::endl;

        delete[] array;
    }

    return 0;
}

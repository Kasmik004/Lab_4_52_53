#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <algorithm>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int start, int end)
{
    int pivot = arr[start];
    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] <= pivot)
            count++;
    }
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex)
    {
        while (arr[i] <= pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i < pivotIndex && j > pivotIndex)
        {
            swap(arr[i++], arr[j--]);
        }
    }
    return pivotIndex;
}

void quickSort(int arr[], int start, int end)
{
    if (start > end)
    {
        return;
    }
    int p = partition(arr, start, end);
    quickSort(arr, start, p - 1);
    quickSort(arr, p + 1, end);
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void testBestCase(int n)
{
    int *bestCaseArr = new int[n];
    for (int i = 0; i < n; i++)
    {
        bestCaseArr[i] = i;
    }
    auto start = chrono::system_clock::now();
    quickSort(bestCaseArr, 0, n - 1);
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Best case execution time for size " << n << ": " << duration.count() << " microseconds" << endl;
    delete[] bestCaseArr;
}

void testWorstCase(int n)
{
    int *worstCaseArr = new int[n];
    for (int i = 0; i < n; i++)
    {
        worstCaseArr[i] = i;
    }
    reverse(worstCaseArr, worstCaseArr + n); // Worst case array
    auto start = chrono::system_clock::now();
    quickSort(worstCaseArr, 0, n - 1);
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Worst case execution time for size " << n << ": " << duration.count() << " microseconds" << endl;
    delete[] worstCaseArr;
}

void testRandomCase(int n)
{
    int *randArr = new int[n];
    for (int i = 0; i < n; i++)
    {
        randArr[i] = rand() % 200;
    }
    auto start = chrono::system_clock::now();
    quickSort(randArr, 0, n - 1);
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Random case execution time for size " << n << ": " << duration.count() << " microseconds" << endl;
    delete[] randArr;
}

int main()
{
    int sizes[] = {10000, 20000, 30000, 40000};
    int len = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < len; i++)
    {
        int n = sizes[i];

        testRandomCase(n);
        testBestCase(n);
        testWorstCase(n);
    }

    return 0;
}

#include <utility>

#include "sort.h"

void sel_sort(int *array, const int size)
{
    for(int i = 0; i < size - 1; ++i)
    {
        int min_i = i;
        for(int j = i + 1; j < size; ++j)
        {
            if(array[j] < array[min_i])
                min_i = j;
        }

        if(min_i != i)
        {
            std::swap(array[i], array[min_i]);
            min_i = i;
        }
    }
}

void shaker_sort(int *array, const int size)
{
    for(int left = 0, right = size -1; left < right;)
    {
        for(int i = left; i < right; ++i)
        {
            if(array[i + 1] < array[i])
                std::swap(array[i], array[i + 1]);
        }
        --right;

        for(int i = right; i > left; --i)
        {
            if(array[i - 1] > array[i])
                std::swap(array[i - 1], array[i]);
        }
        ++left;
    }
}

void quick_sort(int *array, int N)
{
    int i =0, j = N;
    int p = array[N>>1];

    do
    {
        while(array[i] < p) ++i;
        while(array[j] > p) --j;

        if( i <= j)
        {
            std::swap(array[i], array[j]);
            ++i; --j;
        }
    }while( i<= j);

    if(j > 0) quick_sort(array, j);
    if(N > i) quick_sort(array + i, N - i);
}
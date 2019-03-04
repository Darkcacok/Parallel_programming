#include <omp.h>
#include <iostream>
#include <string.h>

#include "sortmp.h"
#include "sort.h"



int min_search(int *array, int *indexes_values, int size_indxs, int *array_parts, int *part)
{
    int indx_min = indexes_values[0];
    (*part) = array_parts[0];
    for (int i = 1; i < size_indxs; ++i)
        if (array[indx_min] > array[indexes_values[i]])
        {
            indx_min = indexes_values[i];
            (*part) = array_parts[i];
        }

    return indx_min;
}

void merge(int *array, int size, int *to_edge, int parts)
{
    int *tmp = new int[size];
    int *edge = new int[parts];
    int *indexes_values = new int[parts];
    int *array_parts = new int[parts];
    int size_indxs = 0;

    edge[0] = 0;
    for(int i = 1; i < parts; ++i)
        edge[i] = to_edge[i - 1];

    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < parts; ++j)
        {
            if(edge[j] < to_edge[j])
            {
                indexes_values[size_indxs] = edge[j];
                array_parts[size_indxs] = j;
                ++size_indxs;
            }
        }

        int part;
        tmp[i] = array[min_search(array, indexes_values, size_indxs, array_parts, &part)];

        size_indxs = 0; 
        ++edge[part];
    }

    memcpy(array, tmp, sizeof(int) * size);

    delete[] tmp;
}

void sel_sort_mp(int *array, const int size)
{
    int thread = 8;
    int step = size / thread;;
    int *threads = new int[thread];

    omp_set_num_threads(thread);

    for (int i = 0; i < thread - 1; ++i)
    {
        threads[i] = i * step + step;
    }
    threads[thread - 1] = size;

    #pragma omp parallel
    {
        int edge;
        int target_thread = omp_get_thread_num();

        if (target_thread == 0)
            edge = 0;
        else
            edge = threads[target_thread - 1];
        
         for(int i = edge; i < threads[target_thread] - 1; ++i)
         {
            int min_i = i;
            for(int j = i + 1; j < threads[target_thread]; ++j)
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
    merge(array, size, threads, thread);
}

void shaker_sort_mp(int *array, const int size)
{
    int thread = 8; //omp_get_num_threads();
    int *threads = new int[thread];
    int step = size / thread;

    omp_set_num_threads(thread);
    for (int i = 0; i < thread - 1; ++i)
    {
        threads[i] = i * step + step;
    }
    threads[thread - 1] = size;

    #pragma omp parallel
    {
        int edge;
        int target_thread = omp_get_thread_num();

        if (target_thread == 0)
            edge = 0;
        else
            edge = threads[target_thread - 1];

        for (int left = edge, right = threads[target_thread] - 1; left < right;)
        {
            for (int i = left; i < right; ++i)
            {
                if (array[i + 1] < array[i])
                    std::swap(array[i], array[i + 1]);
            }
            --right;

            for (int i = right; i > left; --i)
            {
                if (array[i - 1] > array[i])
                    std::swap(array[i - 1], array[i]);
            }
            ++left;
        }
    }
    merge(array, size, threads, thread);
}

void quick_sort_mp(int *array, int size)
{
    int thread = 8; //omp_get_num_threads();
    int *threads = new int[thread];
    int step = size / thread;

    omp_set_num_threads(thread);
    for (int i = 0; i < thread - 1; ++i)
    {
        threads[i] = i * step + step;
    }
    threads[thread - 1] = size;

    #pragma omp parallel
    {
        int edge;
        int target_thread = omp_get_thread_num();

        if (target_thread == 0)
            edge = 0;
        else
            edge = threads[target_thread - 1];
        
        quick_sort(array + edge, threads[target_thread] - edge - 1);
    }
    merge(array, size, threads, thread);
}
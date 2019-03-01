#include <omp.h>
#include <iostream>
#include <string.h>

#include "sortmp.h"
#include "sort.h"

void test()
{
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < 10; ++i)
        {
            std::cout << "Thread: " << omp_get_thread_num() << "  ";
            std::cout << i << std::endl;
        }
    }

    std::cout << std::endl;
}

int *copy_part_array(int *array, int *part_idx, int size)
{
    int *buf = new int[size];

    for (int i = 0; i < size; ++i)
    {
        buf[i] = array[part_idx[i]];
    }

    return buf;
}

void move_part_array(int *array, int *part_idx, int thread, int edge)
{
    for (int i = edge, j = 0; i < edge + thread && j < thread; ++i, ++j)
    {
        array[part_idx[j]] = array[i];
    }
}

void sort_buf(int *buf, int size)
{
    sel_sort(buf, size);
}

int min_search(int *array, int *min, int size)
{
    int min_idx = min[0];
    for (int i = 1; i < size; ++i)
        if (array[min_idx] > array[min[i]])
            min_idx = min[i];

    return min_idx;
}

void sel_sort_mp(int *array, const int size)
{
    int thread = 8;
    int step;
    int *threads = new int[thread];
    int *min = new int[thread];

    omp_set_num_threads(thread);

    int i = 0;
    for (i; i < size - thread; ++i)
    {
        step = (size - i) / thread;
        for (int j = 0; j < thread - 1; ++j)
        {
            threads[j] = i + j * step + step;
        }
        threads[thread - 1] = size;

        for (int j = 0; j < thread - 1; ++j)
        {
            min[j] = threads[j] - 1;
        }
        min[thread - 1] = size;

        /*int j;
        int target_thread;*/

#pragma omp parallel
        {
            int j;
            int target_thread;
            target_thread = omp_get_thread_num();

            if (target_thread == 0)
                j = i;
            else
                j = threads[target_thread - 1];

            for (j; j < threads[target_thread]; ++j)
            {
                if (array[j] < array[min[target_thread]])
                    min[target_thread] = j;
            }
        }
        /*for(int k = 0; k < thread; ++k)
        {
            std::cout << array[min[k]] << "\t";
        }
        std::cout << std::endl;*/

        std::swap(array[i], array[min_search(array, min, thread)]);
    }

    sort_buf(array + i, size - i);
}

void shaker_sort_mp(int *array, const int size)
{
    /*int *tmp1 = new int[size];
    memcpy(tmp1, array, sizeof(int) * size);

    int *tmp2 = new int[size];
    memcpy(tmp2, array, sizeof(int) * size);

    int part_one = size >> 1;
    int part_two = size - part_one;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0, right = size - 1; i < part_one; ++i, --right)
            {
                for (int j = 0; j < right; ++j)
                {
                    if (tmp1[j + 1] < tmp1[j])
                        std::swap(tmp1[j], tmp1[j + 1]);
                }
            }
        }

        #pragma omp section
        {
            for (int i = 0, left = 0; i < part_two; ++i, ++left)
            {
                for (int j = size; j > left; --j)
                {
                    if (tmp2[j - 1] > tmp2[j])
                        std::swap(tmp2[j - 1], tmp2[j]);
                }
            }
        }
    }

    #pragma omp parallel
    for (int i = part_one; i < size; ++i)
        array[i] = tmp1[i];
    
    #pragma omp parallel
    for (int i = 0; i < part_two; ++i)
        array[i] = tmp2[i];*/
}




void quick_sort_mp(int *array, int N)
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

    #pragma omp parallel sections
    {
        #pragma omp section
        if(j > 0) quick_sort(array, j);
        #pragma omp section
        if(N > i) quick_sort(array + i, N - i);
    }
}
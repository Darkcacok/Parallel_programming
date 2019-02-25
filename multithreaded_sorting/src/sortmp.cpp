#include <omp.h>
#include <iostream>

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

    for(int i = 0; i < size; ++i)
    {
        buf[i] = array[part_idx[i]];
    }

    return buf;
}

void move_part_array(int *array, int *part_idx, int thread, int edge)
{
    for(int i = edge, j = 0; i < edge + thread && j < thread; ++i, ++j)
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
    for(int i = 1; i < size; ++i)
        if(array[min_idx] > array[min[i]])
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

        for (int j = 0; j < thread-1; ++j)
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

    sort_buf(array+i, size - i);
}
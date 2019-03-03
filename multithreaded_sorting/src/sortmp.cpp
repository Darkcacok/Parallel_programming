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

int min_search(int *array, int *min, int size, int *indxs_mins, int *indx)
{
    int min_idx = min[0];
    (*indx) = indxs_mins[0];
    for (int i = 1; i < size; ++i)
        if (array[min_idx] > array[min[i]])
        {
            min_idx = min[i];
            (*indx) = indxs_mins[i];
        }

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

        std::swap(array[i], array[min_search(array, min, thread)]);
    }

    sort_buf(array + i, size - i);
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

    int *tmp = new int[size];
    int *indx = new int[thread];
    int *mins = new int[thread];
    int *indxs_mins = new int[thread];
    int size_mins = 0;

    indx[0] = 0;
    for (int i = 1; i < thread; ++i)
        indx[i] = threads[i - 1];

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < thread; ++j)
        {
            if (indx[j] < threads[j])
            {
                mins[size_mins] = indx[j];
                indxs_mins[size_mins] = j;
                ++size_mins;
            }
        }

        int indx_thread;
        tmp[i] = array[min_search(array, mins, size_mins, indxs_mins, &indx_thread)];
        size_mins = 0;

        ++indx[indx_thread];
    }

    memcpy(array, tmp, sizeof(int) * size);

    delete[] tmp;
}

void quick_sort_mp(int *array, int N)
{
    int i = 0, j = N;
    int p = array[N >> 1];

    do
    {
        while (array[i] < p)
            ++i;
        while (array[j] > p)
            --j;

        if (i <= j)
        {
            std::swap(array[i], array[j]);
            ++i;
            --j;
        }
    } while (i <= j);

#pragma omp parallel sections
    {
#pragma omp section
        if (j > 0)
            quick_sort(array, j);
#pragma omp section
        if (N > i)
            quick_sort(array + i, N - i);
    }
}
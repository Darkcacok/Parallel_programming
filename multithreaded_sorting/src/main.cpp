#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <chrono>

#include "constants.h"
#include "sort.h"
#include "sortmp.h"

bool test(int *array, int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        if (array[i] <= array[i + 1])
            continue;
        else
        {
            std::cout << array[i] << " > " << array[i + 1] << std::endl;
            return false;
        }
    }

    return true;
}

void gen_rand_num(int *array, int size)
{
    srand(time(NULL));

    for (int i = 0; i < size; ++i)
        array[i] = rand_min + rand() % rand_max;
}

int main()
{
    //test();
    int *array = new int[size];
    int *test_array = new int[size];

    //int array[10] = {9, 8, 7, 6, 5, 4, 3, 0, 1, 2};

    gen_rand_num(array, size);
    memcpy(test_array, array, sizeof(int) * size);

    /***************************************************/
    std::cout << "Selection sort is start" << std::endl;

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    sel_sort(array, size);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "time = " << time_span.count() <<std::endl;

    if (test(array, size))
        std::cout << "Sorting is successful" << std::endl;
    else
        std::cout << "Sorting is fail" << std::endl;

    std::cout << "Selection sort is finish" << std::endl << std::endl<< std::endl;

    memcpy(test_array, array, sizeof(int) * size);

    /****************************************************************/
    std::cout << "Selection multithreading sort is start" << std::endl;

    t1 = std::chrono::steady_clock::now();
    sel_sort_mp(array, size);
    t2 = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "time = " << time_span.count() <<std::endl;

    if (test(array, size))
        std::cout << "Sorting is successful" << std::endl;
    else
        std::cout << "Sorting is fail" << std::endl;

    std::cout << "Selection multithreading sort is finish" << std::endl;

}
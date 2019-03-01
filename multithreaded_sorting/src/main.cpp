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


void print(int *array, int size)
{
    std::cout << std::endl;

    for(int i = 0; i < size; ++i)
        std::cout << array[i] << "\t";

    std::cout << std::endl;
}

void gen_rand_num(int *array, int size)
{
    srand(time(NULL));

    for (int i = 0; i < size; ++i)
        array[i] = rand_min + rand() % rand_max;
}

int main()
{
    int *array = new int[size];
    int *test_array = new int[size];

    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;
    std::chrono::duration<double> time_span;

    gen_rand_num(array, size);


    /*---------------Selection sort-----------------------------------------*/
    memcpy(test_array, array, sizeof(int) * size);

    std::cout << "Selection sort is start" << std::endl;

    t1 = std::chrono::steady_clock::now();
    sel_sort(test_array, size);
    t2 = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "One thread time = " << time_span.count();

    if (test(test_array, size))
        std::cout << ". Sorting is successful" << std::endl;
    else
        std::cout << ". Sorting is fail" << std::endl;

    /****************************************************************/

    memcpy(test_array, array, sizeof(int) * size);

    t1 = std::chrono::steady_clock::now();
    sel_sort_mp(test_array, size);
    t2 = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "Multithreading time = " << time_span.count();

    if (test(test_array, size))
        std::cout << ". Sorting is successful" << std::endl;
    else
        std::cout << ". Sorting is fail" << std::endl;

    std::cout << "Selection sort is finish" << std::endl << std::endl;
    
    /*-----------------Shaker sort---------------------------------------------*/
    
    memcpy(test_array, array, sizeof(int) * size);


    std::cout << "Shaker sort is start" << std::endl;

    t1 = std::chrono::steady_clock::now();
    shaker_sort(test_array, size);
    t2 = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "One thread time = " << time_span.count() << " ";


    if (test(test_array, size))
        std::cout << ". Sorting is successful" << std::endl;
    else
        std::cout << ". Sorting is fail" << std::endl;
    /****************************************************************************/

    memcpy(test_array, array, sizeof(int) * size);


    t1 = std::chrono::steady_clock::now();
    shaker_sort_mp(test_array, size);
    t2 = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "Multithreading time = " << time_span.count();

    if (test(test_array, size))
        std::cout << ". Sorting is successful" << std::endl;
    else
        std::cout << ". Sorting is fail" << std::endl;

    std::cout << "Shacker sort is finish" << std::endl << std::endl;


    /*---------------------Quick sort-----------------------------------------------*/
    
    memcpy(test_array, array, sizeof(int) * size);

    std::cout << "Quick sort is start" << std::endl;

    t1 = std::chrono::steady_clock::now();
    quick_sort(test_array, size);
    t2 = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "One thread time = " << time_span.count() << " ";

    if (test(test_array, size - 1))
        std::cout << ". Sorting is successful" << std::endl;
    else
        std::cout << ". Sorting is fail" << std::endl;
    /*******************************************************************************/

    memcpy(test_array, array, sizeof(int) * size);

    t1 = std::chrono::steady_clock::now();
    quick_sort_mp(test_array, size - 1);
    t2 = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "Multithreading time = " << time_span.count();

    if (test(test_array, size))
        std::cout << ". Sorting is successful" << std::endl;
    else
        std::cout << ". Sorting is fail" << std::endl;

    std::cout << "Shacker sort is finish" << std::endl << std::endl;


}
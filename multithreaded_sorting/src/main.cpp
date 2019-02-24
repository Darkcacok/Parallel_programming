#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "sort.h"
#include "sortmp.h"

void gen_rand_num(int *array, int size)
{
    srand(time(NULL));

    for(int i = 0; i < size; ++i)
        array[i] = rand_min + rand() % rand_max;
}

int main()
{
    //test();
    //int *Array = new int[size];

    int Array[10] = {9, 8, 7, 6, 5, 4, 3, 0, 1, 2};

    //gen_rand_num(Array, size);



    for(int i = 0; i < 10; ++i)
        std::cout << Array[i] << "\t";
    
    std::cout << std::endl;

    sel_sort_mp(Array, size);

    for(int i = 0; i < 10; ++i)
        std::cout << Array[i] << "\t";

    std::cout << std::endl;
}
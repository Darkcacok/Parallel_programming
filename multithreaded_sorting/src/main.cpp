#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "sort.h"

void gen_rand_num(int *array)
{
    srand(time(NULL));

    for(int i = 0; i < size; ++i)
        array[i] = rand_min + rand() % rand_max;
}

int main()
{
    int *Array = new int[size];

    gen_rand_num(Array);

    for(int i = 0; i < 10; ++i)
        std::cout << Array[i] << "\t";
    
    std::cout << std::endl;

    quick_sort(Array, size - 1);

    for(int i = 0; i < 10; ++i)
        std::cout << Array[i] << "\t";

    std::cout << std::endl;
}
#ifndef SORTMP_H_
#define SORTMP_H_

//Сортирвока выбором многопоточная
void sel_sort_mp(int *array, const int size);

//Сортировка перемешиванием многопоточная
void shaker_sort_mp(int *array, const int size);

//Быстрая сортировка многопоточная
void quick_sort_mp(int * arr, int N);

#endif //SORTMP_H_
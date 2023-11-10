#include "int.h"
#include <stdlib.h>
int compare_ints(const int *a, const int *b) { return *a - *b; }

int *create_random_int_array(size_t size) {
  int *array = (int *)malloc(size * sizeof(int));
  for (size_t i = 0; i < size; i++)
    array[i] = random();
  return array;
}
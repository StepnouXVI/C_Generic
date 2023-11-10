#include "user_type.h"
#include <stdlib.h>

int compare_structs(const struct_t *a, const struct_t *b) {
  return a->c > b->c ? 1 : a->c < b->c ? -1 : 0;
}

struct_t *make_random_struct_array(size_t size) {
  struct_t *array = (struct_t *)malloc(size * sizeof(struct_t));
  for (size_t i = 0; i < size; i++) {
    array[i].a = random();
    array[i].b = random();
    array[i].c = random();
  }
  return array;
}

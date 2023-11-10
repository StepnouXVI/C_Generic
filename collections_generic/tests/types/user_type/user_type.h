#ifndef STRUCT_FOR_TESTS
#define STRUCT_FOR_TESTS

#include <stddef.h>

typedef struct stuct_t {
  int a;
  int b;
  size_t c;
} struct_t;


int compare_structs(const struct_t *a, const struct_t *b);

struct_t *make_random_struct_array(size_t size);
#endif
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "bool_t.h"
#include <stddef.h>

typedef int (*compare_t)(const void *, const void *);
typedef void (*destruct_t)(void *);
typedef void (*copy_t)(const void *, void *);
typedef bool_t (*predicate_t)(const void *);

typedef void *(*create_t)(void);

typedef size_t (*get_hash_code_t)(size_t capacity, size_t key_gen,
                                 const void *key);
#endif
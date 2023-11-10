#ifndef TYPES_H
#define TYPES_H
#include "../../support/bool_t.h"

typedef bool_t (*predicate_t)(void *);
typedef void *(*selector_t)(void *);
typedef enumerator_t (*selector_many_t)(void *);
#endif
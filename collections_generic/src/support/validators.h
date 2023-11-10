#ifndef VALIDATORS_H
#define VALIDATORS_H
#include "../types/bool_t.h"
bool_t null_check(const char *tag, const char *message, const void *ptr,
                  const char *name, const char *file, const char *func,
                  int line);

#define NULL_ARGUMENT "NULL ARGUMENT ERROR"
#define MALLOC_FAILURE "MALLOC FAILURE ERROR"
#define EMPTY_MESSAGE ""

#define NULL_CHECK(tag, variable, message)                                     \
  null_check(tag, message, (variable), #variable, __FILE__, __FUNCTION__,      \
             __LINE__)

#define NULL_ARGUMENT_CHECK(variable)                                          \
  NULL_CHECK(NULL_ARGUMENT, variable, EMPTY_MESSAGE)
#define MALLOC_FAILURE_CHECK(variable)                                         \
  NULL_CHECK(MALLOC_FAILURE, variable, "Malloc failure.")
#endif
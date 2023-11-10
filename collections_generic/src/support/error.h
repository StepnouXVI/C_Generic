#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

#define ERROR_MESSAGE(message)                                                 \
  fprintf(stderr, "[ERROR][%s][%s]: %s\n", __FILE__, __FUNCTION__, message);
#define NULL_ARGUMENT_ERROR(variable)                                          \
  fprintf(stderr, "[NULL ARGUMENT ERROR][%s][%s]:  %s is NULL\n", __FILE__,    \
          __FUNCTION__, variable);

#endif
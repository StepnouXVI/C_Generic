#include "validators.h"
#include "error.h"

bool_t null_check(const char *tag, const char *message, const void *ptr,
                const char *name, const char *file, const char *func,
                int line) {
  if (ptr != NULL)
    return false;

  fprintf(stderr, "[%s][%s:%d][%s]:  %s is NULL. %s.\n", tag, file, line, func,
          name, message);
  return true;
}
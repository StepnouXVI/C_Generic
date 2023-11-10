#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool_t check_compare(const compare_t compare) {
  if (compare == NULL)
    fprintf(stderr, "compare is NULL\n");

  return compare == NULL;
}

void use_user_destruct_or_default_free(const destruct_t destruct, void *src) {
  if (destruct != NULL)
    destruct(src);
  else
    free(src);
}

void use_user_copy_or_default_memcpy(const copy_t copy, size_t size_of_data,
                                     const void *src, void *dest) {
  if (copy != NULL)
    copy(src, dest);
  else
    memcpy(dest, src, size_of_data);
}

#include "type_manager_functions.h"

#include "../../support/validators.h"
#include <stdlib.h>
#include <string.h>

void use_user_copy_or_memcpy(const type_manager_t *type_manager,
                             const void *restrict src, void *restrict dst) {
  if (NULL_ARGUMENT_CHECK(src) || NULL_ARGUMENT_CHECK(dst) || NULL_ARGUMENT_CHECK(type_manager))
    return;

  if (type_manager->copy) {
    type_manager->copy(src, dst);
  } else {
    memcpy(dst, src, type_manager->size_of_obj);
  }
}

void use_user_destruct_or_free(type_manager_t *type_manager, void *obj) {
  if (obj == NULL || NULL_ARGUMENT_CHECK(type_manager))
    return;

  if (type_manager->destruct) {
    type_manager->destruct(obj);
  } else {
    free(obj);
  }
}
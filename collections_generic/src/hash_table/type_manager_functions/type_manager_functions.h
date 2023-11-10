#ifndef TYPE_MANAGER_FUNCTIONS_H
#define TYPE_MANAGER_FUNCTIONS_H

#include "../types/type_manager.h"

void use_user_copy_or_memcpy(const type_manager_t *type_manager,
                             const void *restrict src, void *restrict dst);
void use_user_destruct_or_free(type_manager_t *type_manager, void *obj);

#endif
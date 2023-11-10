#ifndef HELPER_FOR_LINKED_LIST
#define HELPER_FOR_LINKED_LIST
#include "../../types/bool_t.h"
#include "../../types/functions.h"

bool_t check_compare(const compare_t compare);
void use_user_destruct_or_default_free(const destruct_t destruct, void *src);
void use_user_copy_or_default_memcpy(const copy_t copy, size_t size_of_data,
                                     const void *src, void *dest);
#endif
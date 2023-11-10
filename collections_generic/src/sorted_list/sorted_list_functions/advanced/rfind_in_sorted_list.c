#include "../../sorted_list.h"
#include "../../../linked_list/linked_list.h"


size_t r_find_in_sorted_list(const sorted_list_t *list, const void *data) {
  return r_find_in_linked_list((linked_list_t*)list, data);
}
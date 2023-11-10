#include "../../sorted_list.h"
#include "../../../linked_list/linked_list.h"


void *get_by_index_from_sorted_list(const sorted_list_t *list, size_t index) {
  return get_by_index_from_linked_list((linked_list_t *)list, index);
}
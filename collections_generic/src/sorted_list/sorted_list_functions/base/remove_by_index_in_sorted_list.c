
#include "../../sorted_list.h"
#include "../../../linked_list/linked_list.h"


bool_t remove_by_index_from_sorted_list(sorted_list_t *list, size_t index) {
  return remove_by_index_from_linked_list((linked_list_t *)list, index);
}
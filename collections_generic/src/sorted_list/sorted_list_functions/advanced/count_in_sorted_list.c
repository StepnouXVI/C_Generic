#include "../../sorted_list.h"
#include "../../../linked_list/linked_list.h"


size_t count_in_sorted_list(const sorted_list_t *list, const void *data) {
  return count_in_linked_list((const linked_list_t *)list, data);
}
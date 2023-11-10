#include "../../sorted_list.h"
#include "../../../linked_list/linked_list.h"


bool_t contains_in_sorted_list(const sorted_list_t *list, const void *data) {
  return contains_in_linked_list((const linked_list_t*)list, data);
}
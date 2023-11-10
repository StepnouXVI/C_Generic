#include "../../sorted_list.h"
#include "../../../linked_list/linked_list.h"


bool_t remove_all_from_sorted_list(sorted_list_t *list, const void *data) {
  return remove_all_from_linked_list((linked_list_t *)list, data);
}

#include "../../sorted_list.h"
#include "../../../linked_list/linked_list.h"


bool_t get_by_index_with_copy_from_sorted_list(const sorted_list_t *list,
                                             size_t index, void *data) {

  return get_by_index_with_copy_from_linked_list((linked_list_t *)list, index,
                                                 data);
}
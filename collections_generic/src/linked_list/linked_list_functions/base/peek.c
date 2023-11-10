#include "base_functions.h"
#include "../../helper/helper.h"

bool_t peek_front(const struct linked_list_t *list, void *data) {
  if (is_empty_list(list))
    return false;

  use_user_copy_or_default_memcpy(list->copy, list->size_of_data, list->head->data, data);
  return true;
}

bool_t peek_back(const struct linked_list_t *list, void *data) {
  if (is_empty_list(list))
    return false;

  use_user_copy_or_default_memcpy(list->copy, list->size_of_data, list->tail->data, data);
  return true;
}
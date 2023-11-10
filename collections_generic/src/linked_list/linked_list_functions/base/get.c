#include "../../../support/error.h"
#include "../../helper/helper.h"
#include "base_functions.h"

void *get_by_index_from_linked_list(const linked_list_t *list, size_t index) {
  if (index >= list->size) {
    ERROR_MESSAGE("index out of range");
    return NULL;
  }

  node_t *current = list->head;
  size_t i = 0;
  while (i < index) {
    current = current->next;
    i++;
  }

  return current->data;
}

bool_t get_by_index_with_copy_from_linked_list(const linked_list_t *list,
                                             size_t index, void *data) {
  void *res = get_by_index_from_linked_list(list, index);
  if (res == NULL || data == NULL)
    return false;

  use_user_copy_or_default_memcpy(list->copy, list->size_of_data, res, data);
  return true;
}

size_t get_size_of_linked_list(const linked_list_t *list) {
  return list->size;
}
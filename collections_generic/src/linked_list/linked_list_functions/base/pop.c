#include "../../helper/helper.h"
#include "../../node_functions/node_functions.h"
#include "base_functions.h"

bool_t pop_back(linked_list_t *list, void *data) {
  if (is_empty_list(list)) {
    return false;
  }

  node_t *last_node = list->tail;
  use_user_copy_or_default_memcpy(list->copy, list->size_of_data,
                                  last_node->data, data);

  if (list->size == 1) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list->tail = last_node->perv;
    list->tail->next = NULL;
  }

  list->size--;
  destruct_node_and_data(list->destruct, last_node);
  return true;
}

bool_t pop_front(linked_list_t *list, void *data) {
  if (is_empty_list(list)) {
    return false;
  }

  node_t *first_node = list->head;
  use_user_copy_or_default_memcpy(list->copy, list->size_of_data,
                                  first_node->data, data);

  if (list->size == 1) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list->head = first_node->next;
    list->head->perv = NULL;
  }

  list->size--;
  destruct_node_and_data(list->destruct, first_node);
  return true;
}
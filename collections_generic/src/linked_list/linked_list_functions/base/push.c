#include "../../../support/validators.h"
#include "../../node_functions/node_functions.h"
#include "base_functions.h"

void push_back(struct linked_list_t *list, const void *data) {
  if (data == NULL || NULL_ARGUMENT_CHECK(list))
    return;

  node_t *node =
      create_node_and_copy_data(list->copy, list->size_of_data, data);

  if (is_empty_list(list)) {
    list->head = node;
    list->tail = node;
  } else {
    node->perv = list->tail;
    list->tail->next = node;
    list->tail = node;
  }
  list->size++;
}

void push_front(struct linked_list_t *list, const void *data) {

  if (data == NULL || NULL_ARGUMENT_CHECK(list))
    return;

  node_t *node =
      create_node_and_copy_data(list->copy, list->size_of_data, data);

  if (is_empty_list(list)) {
    list->head = node;
    list->tail = node;
  } else {
    list->head->perv = node;
    node->next = list->head;
    list->head = node;
  }
  list->size++;
}
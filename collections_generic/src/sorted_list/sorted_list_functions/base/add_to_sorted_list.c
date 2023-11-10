#include "../../../support/validators.h"
#include "../../sorted_list.h"
#include "../../../linked_list/linked_list.h"
#include "../../../linked_list/node_functions/node_functions.h"


void add_to_sorted_list(sorted_list_t *list, const void *data) {

  if (NULL_ARGUMENT_CHECK(list) || NULL_ARGUMENT_CHECK(data)) {
    return;
  }

  node_t *new_node =
      create_node_and_copy_data(list->copy, list->size_of_data, data);

  // Insert the new node into the list in the appropriate position
  node_t *current = list->head;
  node_t *previous = NULL;
  while (current != NULL && list->compare(current->data, data) < 0) {
    previous = current;
    current = current->next;
  }
  if (previous == NULL) {
    // Insert the new node at the head of the list
    new_node->next = list->head;
    if (list->head != NULL) {
      list->head->perv = new_node;
    } else {
      list->tail = new_node;
    }
    list->head = new_node;
  } else {
    // Insert the new node after the previous node
    new_node->next = previous->next;
    new_node->perv = previous;
    if (previous->next != NULL) {
      previous->next->perv = new_node;
    } else {
      list->tail = new_node;
    }
    previous->next = new_node;
  }

  // Update the size of the list
  list->size++;
}


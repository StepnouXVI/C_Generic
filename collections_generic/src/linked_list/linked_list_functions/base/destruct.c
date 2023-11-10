#include "../../node_functions/node_functions.h"
#include "base_functions.h"
#include <stdlib.h>
void destruct_linked_list(linked_list_t *list) {
  if (list == NULL) {
    return;
  }

  node_t *current_node = list->head;
  node_t *next_node = NULL;

  while (current_node != NULL) {
    next_node = current_node->next;
    destruct_node_and_data(list->destruct, current_node);
    current_node = next_node;
  }

  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
}
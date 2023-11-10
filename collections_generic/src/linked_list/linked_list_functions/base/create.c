#include "base_functions.h"
#include <stdio.h>
#include <stdlib.h>

linked_list_t *create_linked_list(size_t size_of_data, compare_t compare,
                                  destruct_t destruct, copy_t copy) {
  linked_list_t *list = (linked_list_t *)malloc(sizeof(linked_list_t));

  list->size_of_data = size_of_data;
  list->compare = compare;
  list->destruct = destruct;
  list->copy = copy;
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}
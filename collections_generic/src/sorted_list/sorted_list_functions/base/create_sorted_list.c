#include "../../../support/validators.h"
#include "../../sorted_list.h"
#include "../../../linked_list/linked_list.h"

#include <stdlib.h>

sorted_list_t *create_sorted_list(size_t size_of_data, copy_t copy,
                                  destruct_t destruct, compare_t compare) {

  if (NULL_ARGUMENT_CHECK(copy) || NULL_ARGUMENT_CHECK(destruct) ||
      NULL_ARGUMENT_CHECK(compare)) {
    return NULL;
  }

  sorted_list_t *list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
  if (MALLOC_FAILURE_CHECK(list)) {
    return NULL;
  }

  list->copy = copy;
  list->destruct = destruct;
  list->compare = compare;
  list->size_of_data = size_of_data;
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  return list;
}
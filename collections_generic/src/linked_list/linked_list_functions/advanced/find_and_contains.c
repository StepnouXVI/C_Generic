#include "../../helper/helper.h"
#include "../../node_functions/node_functions.h"
#include "advanced_functions.h"

bool_t contains_in_linked_list(const linked_list_t*list, const void *data) {
  if (list == NULL || check_compare(list->compare)) return false;
  bool_t isExist = false;

  node_t *current = list->head;
  while (current != NULL && !isExist) {
    if (list->compare(current->data, data) == 0) {
      isExist = true;
    }
    current = current->next;
  }

  return isExist;
}

size_t count_in_linked_list(const linked_list_t*list, const void *data) {
  if (list == NULL || check_compare(list->compare)) return false;

  size_t count = 0;
  node_t *current = list->head;
  
  while (current) {
    if (list->compare(current->data, data) == 0) count++;

    current = current->next;
  }

  return count;
}

long long int find_in_linked_list(const linked_list_t*list, const void *data) {
  if (list == NULL || check_compare(list->compare)) return false;

  node_t *current = list->head;
  long long int index = 0;

  while (current) {
    if (list->compare(current->data, data) == 0) {
      return index;
    }
    current = current->next;
    index++;
  }

  return -1;
}

long long int r_find_in_linked_list(const linked_list_t*list, const void *data) {
  if (list == NULL || check_compare(list->compare)) return false;

  node_t *current = list->tail;
  long long int index = list->size - 1;

  while (current) {
    if (list->compare(current->data, data) == 0) {
      return index;
    }
    current = current->perv;
    index--;
  }

  return -1;
}

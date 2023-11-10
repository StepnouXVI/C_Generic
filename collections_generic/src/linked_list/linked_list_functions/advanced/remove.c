#include "../../helper/helper.h"
#include "../../node_functions/node_functions.h"
#include "advanced_functions.h"

static void CorrectingReferencesForRemove(linked_list_t *list,
                                          node_t *current) {
  if (current->perv == NULL) {
    list->head = current->next;
  } else {
    current->perv->next = current->next;
  }

  if (current == list->tail) {
    list->tail = current->perv;
  }
}

bool_t remove_by_index_from_linked_list(linked_list_t *list, size_t index) {
  if (list == NULL || index >= list->size || check_compare(list->compare) ||
      is_empty_list(list))
    return false;

  node_t *current = list->head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }
  CorrectingReferencesForRemove(list, current);
  list->size--;
  destruct_node_and_data(list->destruct, current);

  return true;
}

bool_t remove_from_linked_list(linked_list_t *list, const void *data) {
  if (list == NULL || data == NULL || list->size == 0 ||
      check_compare(list->compare))
    return false;

  node_t *current = list->head;
  bool_t break_code = false;

  while (current != NULL && !break_code) {
    if (list->compare(current->data, data) == 0) {
      CorrectingReferencesForRemove(list, current);
      list->size--;
      destruct_node_and_data(list->destruct, current);

      break_code = true;
    } else {
      current = current->next;
    }
  }

  return break_code;
}

bool_t remove_all_from_linked_list(linked_list_t *list, const void *data) {
  if (!list || !data || !list->size || check_compare(list->compare)) {
    return false;
  }

  node_t *prev_node = NULL;
  node_t *current = list->head;
  bool_t removed = false;

  while (current) {
    if (list->compare(current->data, data) == 0) {
      CorrectingReferencesForRemove(list, current);
      destruct_node_and_data(list->destruct, current);
      list->size--;

      current = prev_node ? prev_node->next : list->head;
      removed = true;
    } else {
      prev_node = current;
      current = current->next;
    }
  }

  return removed;
}
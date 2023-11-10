#ifndef LINKED_LIST_T_H
#define LINKED_LIST_T_H

#include "../../types/functions.h"
#include "node_t.h"
#include <stdlib.h>

/**
 * @brief A linked list data structure.
 *
 * @details This structure represents a linked list, and contains a size field,
 * pointers to the first and last nodes in the list, and the size of the data to
 * be stored in the list. The size field represents the number of nodes in the
 * list, and the first and last node pointers are used to traverse the list. The
 * size of the data to be stored in the list is determined when the linked list
 * is initialized using the init_linked_list macro.
 *
 * @param head Pointer to the first node in the linked list.
 * @param tail Pointer to the last node in the linked list.
 * @param size Number of nodes in the linked list.
 * @param size_of_data size of the data to be stored in the linked list.
 * @param compare Function for comparing elements in the sorted list.
 * @param destroy Function for freeing memory occupied by list elements.
 * @param copy Function for creating a copy of an object.
 */
typedef struct linked_list_t {
  node_t *head;        /**< Pointer to the first node in the linked list. */
  node_t *tail;        /**< Pointer to the last node in the linked list. */
  size_t size;         /**< Number of nodes in the linked list. */
  size_t size_of_data; /**< size of the data to be stored in the linked list. */
  compare_t compare;   /**< Function for comparing elements in the sorted list.
                          This function should return a negative number if the
                          first element is less than the second, zero if the two
                          elements are equal, and a positive number if the first
                          element is greater than the second. */
  destruct_t destruct; /**< Function for freeing memory occupied by list
                  elements. This function should take a void pointer to the data
                  to be freed as its only parameter. */
  copy_t copy;         /**< Function for creating a copy of an object. */
} linked_list_t;

#endif
#ifndef ADVANCED_FUNCTIONS_LINKED_LIST_H
#define ADVANCED_FUNCTIONS_LINKED_LIST_H

#include "../../types/linked_list_t.h"
#include "../base/base_functions.h"

/**
 * @brief Checks if a linked list contains a given element.
 *
 * @details This function takes a pointer to a linked list and a pointer to the
 * element to be searched for. It returns true if the element is found in the
 * list, and false otherwise.
 *
 * @param list Pointer to the linked list to be searched.
 * @param data Pointer to the element to be searched for.
 * @return True if the element is found in the list, false otherwise.
 */
bool_t contains_in_linked_list(const linked_list_t *list, const void *data);

/**
 * @brief counts the number of occurrences of an element in a linked list.
 *
 * @details This function takes a pointer to a linked list and a pointer to the
 * element to be searched for. It returns the number of occurrences of the
 * element in the list.
 *
 * @param list Pointer to the linked list to be searched.
 * @param data Pointer to the element to be searched for.
 * @return The number of occurrences of the element in the list.
 */
size_t count_in_linked_list(const linked_list_t *list, const void *data);

/**
 * @brief Removes a node at a given index from a linked list and returns its
 * data.
 *
 * @details This function takes a pointer to a linked list and an index value,
 * and returns true if the node was successfully removed, and false otherwise.
 * If the operation is successful, the data stored in the removed node is stored
 * in the buffer pointed to by data.
 *
 * @param list Pointer to the linked list from which the node will be removed.
 * @param index The index value of the node to be removed.
 * @return True if the operation was successful, false otherwise.
 */
bool_t remove_by_index_from_linked_list(linked_list_t *list, size_t index);

/**
 * @brief Removes the first occurrence of an element from a linked list and
 * returns its data.
 *
 * @details This function takes a pointer to a linked list and a pointer to the
 * element to be removed. It removes the first occurrence of the element from
 * the list, and returns true if the element was found and removed, and false
 * otherwise. If the operation is successful, the data stored in the removed
 * node is stored in the buffer pointed to by data.
 *
 * @param list Pointer to the linked list from which the element will be
 * removed.
 * @param data Pointer to the element to be removed.
 * @return True if the operation was successful, false otherwise.
 */
bool_t remove_from_linked_list(linked_list_t *list, const void *data);

/**
 * @brief Removes all occurrences of an element from a linked list.
 *
 * @details This function takes a pointer to a linked list and a pointer to the
 * element to be removed. It removes all occurrences of the element from the
 * list, and returns true if the element was found and removed at least once,
 * and false otherwise.
 *
 * @param list Pointer to the linked list from which the element will be
 * removed.
 * @param data Pointer to the element to be removed.
 * @return True if the operation was successful, false otherwise.
 */
bool_t remove_all_from_linked_list(linked_list_t *list, const void *data);

/**
 * Finds the first occurrence of an element in a linked list.
 * @param list Pointer to the linked list.
 * @param data Pointer to the element to find.
 * @return The index of the first occurrence of the element in the linked list, if found; -1 if the element is not found.
 */
long long int find_in_linked_list(const linked_list_t *list, const void *data);

/**
 * Finds the last occurrence of an element in a linked list.
 * @param list Pointer to the linked list.
 * @param data Pointer to the element to find.
 * @return The index of the last occurrence of the element in the linked list, if found; -1 if the element is not found.
 */
long long int r_find_in_linked_list(const linked_list_t *list, const void *data);



#endif  // ADVANCED_FUNCTIONS_LINKED_LIST_H
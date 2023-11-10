#ifndef  SORTED_LIST_H
#define SORTED_LIST_H


#include "../linked_list/types/node_t.h"
#include "../types/functions.h"

/**
 * @brief Struct for a sorted linked list.
 *
 * @details This struct defines a sorted linked list. The linked list is sorted
 * in ascending order based on a comparison function provided by the user.
 *
 * @param head Pointer to the first node in the sorted list.
 * @param tail Pointer to the last node in the sorted list.
 * @param size Number of nodes in the sorted list.
 * @param size_of_data size of the data to be stored in the sorted list.
 * @param compare Function for comparing elements in the sorted list.
 * @param destroy Function for freeing memory occupied by list elements.
 */
typedef struct sorted_list_t {
  node_t *head;        /**< Pointer to the first node in the sorted list. */
  node_t *tail;        /**< Pointer to the last node in the sorted list. */
  size_t size;         /**< Number of nodes in the sorted list. */
  size_t size_of_data; /**< size of the data to be stored in the sorted list. */
  copy_t copy;
  destruct_t destruct;
  compare_t compare;
} sorted_list_t;

/**
 * @brief Adds an element to a sorted linked list.
 *
 * @details This function takes a pointer to a sorted linked list and a pointer
 * to the element to be added. It allocates memory for a new node, copies the
 * data into the node, and inserts the node into the sorted list in the
 * appropriate order based on the comparison function provided by the user.
 *
 * @param list Pointer to the sorted linked list to which the element will be
 * added.
 * @param data Pointer to the element to be added.
 */
void add_to_sorted_list(sorted_list_t *list, const void *data);

/**
 * @brief Returns a pointer to the data stored in a node at a given index in a
 * sorted list.
 *
 * @details This function takes a pointer to a sorted linked list and an index
 * value, and returns a pointer to the data stored in the node at that index. If
 * the index is out of bounds, the function returns NULL.
 *
 * @param list Pointer to the sorted linked list to be searched.
 * @param index The index value of the node whose data is to be returned.
 * @return Pointer to the data stored in the node at the given index, or NULL if
 * the index is out of bounds.
 */
void *get_by_index_from_sorted_list(const sorted_list_t *list, size_t index);

/**
 * @brief Copies data from a node at a given index in a sorted list.
 *
 * @details This function takes a pointer to a sorted linked list, an index
 * value, and a pointer to a buffer where the data will be stored. It copies the
 * data from the node at the specified index into the buffer, and returns true
 * if the operation was successful, and false otherwise.
 *
 * @param list Pointer to the sorted linked list to be searched.
 * @param index The index value of the node whose data is to be copied.
 * @param data Pointer to a buffer where the data will be stored.
 * @return True if the operation was successful, false otherwise.
 */
bool_t get_by_index_with_copy_from_sorted_list(const sorted_list_t *list,
                                             size_t index, void *data);

/**
 * @brief Frees memory occupied by a sorted linked list.
 *
 * @details This function takes a pointer to a sorted linked list and frees
 * the memory occupied by the list and all its nodes. It also frees the memory
 * occupied by the data stored in the nodes using the destructor function
 * provided by the user.
 *
 * @param list Pointer to the sorted linked list to be destroyed.
 */
void destruct_sorted_list(sorted_list_t *list);

/**
 * @brief Searches for an element in a sorted linked list.
 *
 * @details This function takes a pointer to a sorted linked list and a pointer
 * to the element to be searched for. It returns true if the element is found in
 * the list, and false otherwise.
 *
 * @param list Pointer to the sorted linked list to be searched.
 * @param data Pointer to the element to be searched for.
 * @return True if the element is found in the list, false otherwise.
 */
bool_t contains_in_sorted_list(const sorted_list_t *list, const void *data);

/**
 * @brief Searches for an element in a sorted linked list.
 *
 * @details This function takes a pointer to a sorted linked list and a pointer
 * to the element to be searched for. It returns the index of the first
 * occurrence of the element in the list, or -1 if the element is not found.
 *
 * @param list Pointer to the sorted linked list to be searched.
 * @param data Pointer to the element to be searched for.
 * @return The index of the first occurrence of the element in the list, or -1
 * if the element is not found.
 */
size_t find_in_sorted_list(const sorted_list_t *list, const void *data);

/**
 * @brief Removes a node at a given index from a sorted linked list.
 *
 * @details This function takes a pointer to a sorted linked list and an index
 * value, and removes the node at that index. It returns true if the operation
 * was successful, and false otherwise. If the operation is successful, the data
 * stored in the removed node is freed using the destructor function provided by
 * the user.
 *
 * @param list Pointer to the sorted linked list from which the node will be
 * removed.
 * @param index The index value of the node to be removed.
 * @return True if the operation was successful, false otherwise.
 */
bool_t remove_by_index_from_sorted_list(sorted_list_t *list, size_t index);

/**
 * @brief Removes the first occurrence of an element from a sorted linked list.
 *
 * @details This function takes a pointer to a sorted linked list and a pointer
 * to the element to be removed. It removes the first occurrence of the element
 * from the list, and returns true if the element was found and removed, and
 * false otherwise. If the operation is successful, the data stored in the
 * removed node is freed using the destructor function provided by the user.
 *
 * @param list Pointer to the sorted linked list from which the element will be
 * removed.
 * @param data Pointer to the element to be removed.
 * @return True if the operation was successful, false otherwise.
 */
bool_t remove_from_sorted_list(sorted_list_t *list, const void *data);

/**
 * @brief Removes all occurrences of an element from a sorted linked list.
 *
 * @details This function takes a pointer to a sorted linked list and a pointer
 * to the element to be removed. It removes all occurrences of the element from
 * the list, and returns true if the element was found and removed at least
 * once, and false otherwise. If the operation is successful, the data stored in
 * the removed nodes is freed using the destructor function provided by the
 * user.
 *
 * @param list Pointer to the sorted linked list from which the element will be
 * removed.
 * @param data Pointer to the element to be removed.
 * @return True if the operation was successful, false otherwise.
 */
bool_t remove_all_from_sorted_list(sorted_list_t *list, const void *data);

/**
 * @brief Searches for an element in a sorted linked list from the end.
 *
 * @details This function takes a pointer to a sorted linked list and a pointer
 * to the element to be searched for. It returns the index of the last
 * occurrence of the element in the list, or -1 if the element is not found.
 *
 * @param list Pointer to the sorted linked list to be searched.
 * @param data Pointer to the element to be searched for.
 * @return The index of the last occurrence of the element in the list, or -1 if
 * the element is not found.
 */
size_t rfind_in_sorted_list(const sorted_list_t *list, const void *data);

/**
 * @brief counts the number of occurrences of an element in a sorted linked
 * list.
 *
 * @details This function takes a pointer to a sorted linked list and a pointer
 * to the element to be counted. It returns the number of occurrences of the
 * element in the list.
 *
 * @param list Pointer to the sorted linked list to be searched.
 * @param data Pointer to the element to be counted.
 * @return The number of occurrences of the element in the list.
 */
size_t count_in_sorted_list(const sorted_list_t *list, const void *data);

sorted_list_t *create_sorted_list(size_t size_of_data, copy_t copy,
                                  destruct_t destruct, compare_t compare);


#define init_sorted_list(type, destructor, copy, compare) create_sorted_list(sizeof(type), copy, destructor, compare)

#endif
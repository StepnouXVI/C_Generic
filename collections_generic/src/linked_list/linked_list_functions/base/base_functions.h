#ifndef LINKED_LIST_BASE_FUNCTIONS_H
#define LINKED_LIST_BASE_FUNCTIONS_H

#include "../../types/linked_list_t.h"

/**
 * @brief Creates a new linked list with the specified parameters.
 *
 * @param size_of_data The size of the data to be stored in the linked list.
 * @param compare Function for comparing elements in the sorted list. This
 * function should return a negative number if the first element is less than
 * the second, zero if the two elements are equal, and a positive number if the
 * first element is greater than the second.
 * @param destruct Function for freeing memory occupied by list elements. This
 * function should take a void pointer to the data to be freed as its only
 * parameter.
 * @param copy Function for copying data to a new location. This function should
 * take two pointers - to the source data and to the destination where the
 * copied data should be stored.
 *
 * @return A pointer to the newly created linked list.
 */
linked_list_t *create_linked_list(size_t size_of_data, compare_t compare,
                                  destruct_t destruct, copy_t copy);

/**
 * @brief Frees the memory occupied by a linked list.
 *
 * @details This function takes a pointer to a linked list, and frees the memory
 * occupied by each node in the list, as well as the memory occupied by the list
 * itself. It calls the destroy function to free the memory occupied by the data
 * stored in each node.
 *
 * @param list Pointer to the linked list to be destructed.
 */
void destruct_linked_list(linked_list_t *list);

/**
 * @brief Checks if a linked list is empty.
 *
 * @details This function takes a pointer to a linked list, and returns true if
 * the list is empty (i.e. has no nodes), and false otherwise.
 *
 * @param list Pointer to the linked list to be checked.
 * @return True if the linked list is empty, false otherwise.
 */
bool_t is_empty_list(const struct linked_list_t *list);

/**
 * @brief Returns the data stored in the front node of a linked list.
 *
 * @details This function takes a pointer to a linked list and a pointer to a
 * buffer where the data will be stored. It copies the data from the front node
 * of the list into the buffer, and returns true if the list is not empty, and
 * false otherwise.
 *
 * @param list Pointer to the linked list to be peeked.
 * @param data Pointer to a buffer where the data will be stored.
 * @return True if the front node of the linked list contains data, false
 * otherwise.
 */
bool_t peek_front(const struct linked_list_t *list, void *data);

/**
 * @brief Returns the data stored in the back node of a linked list.
 *
 * @details This function takes a pointer to a linked list and a pointer to a
 * buffer where the data will be stored. It copies the data from the back node
 * of the list into the buffer, and returns true if the list is not empty, and
 * false otherwise.
 *
 * @param list Pointer to the linked list to be peeked.
 * @param data Pointer to a buffer where the data will be stored.
 * @return True if the back node of the linked list contains data, false
 * otherwise.
 */
bool_t peek_back(const struct linked_list_t *list, void *data);

/**
 * @brief Adds a new node to the back of a linked list.
 *
 * @details This function takes a pointer to a linked list and a pointer to the
 * data to be stored in the new node. It creates a new node with the specified
 * data, and adds it to the back of the linked list.
 *
 * @param list Pointer to the linked list to which the new node will be added.
 * @param data Pointer to the data to be stored in the new node.
 */
void push_back(struct linked_list_t *list, const void *data);

/**
 * @brief Adds a new node to the front of a linked list.
 *
 * @details This function takes a pointer to a linked list and a pointer to the
 * data to be stored in the new node. It creates a new node with the specified
 * data, and adds it to the front of the linked list.
 *
 * @param list Pointer to the linked list to which the new node will be added.
 * @param data Pointer to the data to be stored in the new node.
 */
void push_front(struct linked_list_t *list, const void *data);

/**
 * @brief Removes the back node from a linked list and returns its data.
 *
 * @details This function takes a pointer to a linked list and a pointer to a
 * buffer where the data will be stored. It removes the back node from the list,
 * copies its data into the buffer, and returns true if the list is not empty,
 * and false otherwise.
 *
 * @param list Pointer to the linked list from which the back node will be
 * removed.
 * @param data Pointer to a buffer where the data will be stored.
 * @return True if the back node of the linked list contains data, false
 * otherwise.
 */
bool_t pop_back(linked_list_t *list, void *data);

/**
 * @brief Removes the front node from a linked list and returns its data.
 *
 * @details This function takes a pointer to a linked list and a pointer to a
 * buffer where the data will be stored. It removes the front node from the
 * list, copies its data into the buffer, and returns true if the list is not
 * empty, and false otherwise.
 *
 * @param list Pointer to the linked list from which the front node will be
 * removed.
 * @param data Pointer to a buffer where the data will be stored.
 * @return True if the front node of the linked list contains data, false
 * otherwise.
 */
bool_t pop_front(linked_list_t *list, void *data);

/**
 * @brief Returns a pointer to the data stored in a node at a given index in the
 * list.
 *
 * @details This function takes a pointer to a linked list and an index value,
 * and returns a pointer to the data stored in the node at that index. If the
 * index is out of bounds, the function returns NULL.
 *
 * @param list Pointer to the linked list to be searched.
 * @param index The index value of the node whose data is to be returned.
 * @return Pointer to the data stored in the node at the given index, or NULL if
 * the index is out of bounds.
 */
void *get_by_index_from_linked_list(const linked_list_t *list, size_t index);

/**
 * @brief Copies data from a node at a given index in the list.
 *
 * @details This function takes a pointer to a linked list, an index value, and
 * a pointer to a buffer where the data will be stored. It copies the data from
 * the node at the specified index into the buffer, and returns true if the
 * operation was successful, and false otherwise.
 *
 * @param list Pointer to the linked list to be searched.
 * @param index The index value of the node whose data is to be copied.
 * @param data Pointer to a buffer where the data will be stored.
 * @return True if the operation was successful, false otherwise.
 */
bool_t get_by_index_with_copy_from_linked_list(const linked_list_t *list,
                                             size_t index, void *data);

/**
 * @brief Returns the number of elements in a linked list.
 *
 * @details This function takes a pointer to a linked list and returns its size.
 *
 * @param list Pointer to the linked list.
 * @return Size of the linked list.
 */
size_t get_size_of_linked_list(const linked_list_t *list);

/**
 * @brief Initializes a linked list with the specified parameters.
 *
 * @details This macro takes three arguments: the type of data to be stored in
 * the linked list, a function pointer to a comparison function for the data,
 * and a function pointer to a destructor function for the data. It initializes
 * a new linked list with these parameters, and returns the initialized list.
 *
 * @param type The type of data to be stored in the linked list.
 * @param comparer Function pointer to a comparison function for the data.
 * @param destructor_for_data Function pointer to a destructor function for the
 * data.
 * @param copy_for_data Function pointer to a copy function for the data.
 * @return The initialized linked list.
 */
#define init_linked_list(type, comparer, destructor_for_data, copy_for_data)   \
  create_linked_list(sizeof(type), comparer, destructor_for_data, copy_for_data)
#endif

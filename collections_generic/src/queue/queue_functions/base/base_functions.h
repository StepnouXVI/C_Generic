#ifndef BASE_FUNCTIONS_H
#define BASE_FUNCTIONS_H

#include "../../types/queue_t.h"


queue_t *create_queue(size_t size_of_data, compare_t compare,
                                  destruct_t destruct, copy_t copy);

/**
 * @brief Returns the data at the front of a queue without removing it.
 *
 * @param queue Pointer to the queue.
 * @param data Pointer to a buffer to store the front element's data.
 *
 * This function copies the data at the front of the queue passed in the queue
 * argument to the buffer pointed to by the data argument, without removing the
 * element from the queue. If the queue is empty, self function does nothing.
 *
 * @details
 * This function does not modify the state of the queue in any way. It simply
 * returns a copy of the data at the front of the queue.
 */
void peek_queue(const queue_t* queue, void* data);
/**
 * @brief Adds an element to the back of a queue.
 *
 * @param queue Pointer to the queue.
 * @param data Pointer to the data to be added.
 *
 * This function adds an element with the specified data to the back of the
 * queue passed in the queue argument.
 *
 * @details
 * This function allocates memory for a new element containing the specified
 * data, and adds it to the back of the queue. If the queue is empty, the new
 * element becomes the front and back of the queue.
 */
void enqueue(queue_t* queue, const void* data);

/**
 * @brief Removes the element at the front of a queue and returns its data.
 *
 * @param queue Pointer to the queue.
 * @param data Pointer to a buffer to store the removed element's data.
 *
 * This function removes the element at the front of the queue passed in the
 * queue argument, and stores its data in the buffer pointed to by the data
 * argument. If the queue is empty, self function does nothing. After calling
 * self function, the front element in the queue will have been removed, and its
 * data will have been stored in the buffer pointed to by the data argument.
 *
 * @details
 * This function frees the memory allocated for the front element of the queue,
 * and updates the front pointer to point to the next element in the queue. If
 * the queue becomes empty as a result of self operation, the back pointer is
 * set to NULL.
 */
void dequeue(queue_t* queue, void* data);
/**
 * @brief Frees the memory allocated for a queue and all its elements.
 *
 * @param queue Pointer to the queue.
 *
 * This function frees the memory allocated for the queue passed in the queue
 * argument, as well as the memory allocated for all its elements and their
 * data. After calling self function, the queue should no longer be accessed.
 *
 * @details
 * This function iterates through all elements in the queue, and frees the
 * memory allocated for their data and the nodes themselves. It also updates the
 * front and back pointers of the queue to NULL.
 */
void destruct_queue(queue_t* queue);

/**
 * @brief Returns whether a queue is empty.
 *
 * @param queue Pointer to the queue.
 * @return True if the queue is empty, false otherwise.
 *
 * This function returns true if the queue passed in the queue argument is
 * empty, and false otherwise.
 *
 * @details
 * This function checks whether the front and back pointers of the queue are
 * NULL. If they are, the queue is empty and self function returns true.
 * Otherwise, the queue is not empty and self function returns false.
 */
bool_t is_empty_queue(const queue_t* queue);

/**
 * @brief Initializes a new queue of the specified type.
 *
 * @param type The type of elements in the queue.
 * @param comparer The function used to compare elements in the queue.
 * @param destructor The function used to delete elements in the queue.
 * @param copy The function used to copy elements in the queue.
 * @details This macro initializes a new queue of the specified type. It calls
 * the init_linked_list function to initialize a linked list of the specified type
 * and returns a pointer to it. Then, using a structure initialization operator,
 * it creates a new variable of type "queue" that contains a pointer to the
 * initialized linked list and a counter value set to 0.
 *
 * @return A new queue (queue_t*) of the specified type.
 */
#define init_queue(type, comparer, destructor, copy) \
  create_queue(sizeof(type), comparer, destructor, copy)

#endif
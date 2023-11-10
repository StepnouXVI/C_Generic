#ifndef ADVANCED_FUNCTIONS_QUEUE_H
#define ADVANCED_FUNCTIONS_QUEUE_H
#include "../base/base_functions.h"

/**
 * @brief Checks whether the specified element is present in the queue.
 *
 * @param queue Pointer to the queue.
 * @param data Pointer to the data to be found in the queue.
 * @return True if the element is found, false otherwise.
 *
 * This function takes a pointer to a queue and a pointer to data as arguments,
 * and returns a boolean value indicating whether the specified data is present
 * in the queue. The function iterates through the elements in the queue,
 * starting from the beginning, and compares each element with the specified
 * data using the element comparison function that was passed to the queue
 * during its creation. If the element is found, the function returns true;
 * otherwise, it returns false.
 */
bool_t contains_in_queue(const queue_t* queue, const void* data);
#endif
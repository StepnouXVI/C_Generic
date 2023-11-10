#ifndef QUEUE_T_H
#define QUEUE_T_H
#include "../../linked_list/linked_list.h"
/**
 * @brief A queue data structure.
 *
 * @details This struct represents a queue data structure, which is implemented
 * as a linked list with a front and a back pointer. The front pointer points to
 * the first element in the queue, and the back pointer points to the last
 * element in the queue. The size of the queue is stored in the size field. To
 * create a new queue, use the InitQueue macro.
 */
typedef struct queue_t {
  linked_list_t *list; /**< The linked list underlying the queue. */
  size_t size;     /**< The number of elements in the queue. */
} queue_t;

#endif
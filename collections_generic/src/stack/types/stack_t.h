#ifndef STACK_T_H
#define STACK_T_H

#include "../../linked_list/linked_list.h"

/**
 * @brief A stack data structure.
 *
 * @details This struct represents a stack data structure, which is implemented
 * as a linked list with a top pointer. The top pointer points to the top
 * element in the stack. The size of the stack is stored in the size field. To
 * create a new stack, use the InitStack macro.
 */
typedef struct stack_t {
  linked_list_t  *list; /**< The linked list underlying the stack. */
  size_t size;     /**< The number of elements in the stack. */
} stack_t;


#endif
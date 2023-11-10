#ifndef BASE_FUNCTIONS_STACK_H
#define BASE_FUNCTIONS_STACK_H

#include "../../types/stack_t.h"

/**
 * @brief Returns the data at the top of a stack without removing it.
 *
 * @param stack Pointer to the stack.
 * @param data Pointer to a buffer to store the top element's data.
 *
 *
 * @details
 * This function does not modify the state of the stack in any way. It simply
 * returns a copy of the data at the top of the stack.
 */
void peek_stack(const stack_t *stack, void *data);

/**
 * @brief Removes the element at the top of a stack and returns its data.
 *
 * @param stack Pointer to the stack.
 * @param data Pointer to a buffer to store the popped element's data.
 *
 *
 * @details
 * This function frees the memory allocated for the top element of the stack,
 * and updates the top pointer to point to the next element in the stack. This
 * function removes the element at the top of the stack passed in the stack
 * argument, and stores its data in the buffer pointed to by the data argument.
 * If the stack is empty, self function does nothing.
 * After calling self function, the top element in the stack will have been
 * removed, and its data will have been stored in the buffer pointed to by the
 * data argument.
 */
void pop_stack(stack_t *stack, void *data);

/**
 * @brief Adds an element to the top of a stack.
 *
 * @param stack Pointer to the stack.
 * @param data Pointer to the data to be added.
 *
 *
 * @details
 * This function allocates memory for a new element containing the specified
 * data, and adds it to the top of the stack. If the stack is empty, the new
 * element becomes the top of the stack.
 */
void push_stack(stack_t *stack, const void *data);
/**
 * @brief Frees the memory allocated for a stack and all its elements.
 *
 * @param stack Pointer to the stack.
 *
 *
 * @details
 * This function iterates through all elements in the stack, and frees the
 * memory allocated for their data and the nodes themselves. It also updates the
 * top pointer of the stack to NULL.
 */
void destruct_stack(stack_t *stack);

/**
 * @brief Returns whether a stack is empty.
 *
 * @param stack Pointer to the stack.
 * @return True if the stack is empty, false otherwise.
 *
 *
 * @details
 * This function checks whether the top pointer of the stack is NULL. If it is,
 * the stack is empty and self function returns true. Otherwise, the stack is
 * not empty and self function returns false.
 */
bool_t is_empty_stack(const stack_t *stack);

stack_t *create_stack(size_t size_of_data, compare_t compare,
                      destruct_t destruct, copy_t copy);


#define init_stack(type, comparer, destructor, copy) \
  create_stack(sizeof(type), comparer, destructor, copy)

#endif
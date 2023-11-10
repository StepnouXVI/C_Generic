#ifndef ADVANCED_FUNCTIONS_STACK_H
#define ADVANCED_FUNCTIONS_STACK_H

#include "../base/base_functions.h"

/**
 * @brief Checks if an element is in a stack.
 *
 * @details This function takes a pointer to a stack and a pointer to the
 * element to be searched for, and returns true if the element is found in the
 * stack, and false otherwise. The search begins at the top of the stack, and
 * ends when the element is found or the bottom of the stack is reached.
 *
 * @param stack Pointer to the stack to be searched.
 * @param data Pointer to the element to be searched for.
 * @return True if the element is found in the stack, false otherwise.
 */
bool_t contains_in_stack(const stack_t *stack, const void *data);

#endif
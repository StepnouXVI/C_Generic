#include "advanced_functions.h"

bool_t contains_in_stack(const stack_t *stack, const void *data) {
  return contains_in_linked_list(stack->list, data);
}
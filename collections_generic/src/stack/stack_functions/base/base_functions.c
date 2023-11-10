#include "base_functions.h"

void peek_stack(const stack_t *stack, void *data) {
  peek_front(stack->list, data);
}

void pop_stack(stack_t *stack, void *data) {
  pop_front(stack->list, data);
  stack->size = stack->list->size;
}
void push_stack(stack_t *stack, const void *data) {
  push_front(stack->list, data);
  stack->size = stack->list->size;
}
void destruct_stack(stack_t *stack) {
  destruct_linked_list(stack->list);
  stack->size = 0;
}

bool_t is_empty_stack(const stack_t *stack) { return stack->size == 0; }

stack_t *create_stack(size_t size_of_data, compare_t compare,
                      destruct_t destruct, copy_t copy) {
  stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
  stack->list  = create_linked_list(size_of_data, compare, destruct, copy);
  stack->size = 0;
  return stack;
}
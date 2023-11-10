#include "../../../support/validators.h"
#include "base_functions.h"
void peek_queue(const queue_t *queue, void *data) {
  peek_back(queue->list, data);
}
void enqueue(queue_t *queue, const void *data) {
  push_front(queue->list, data);
  queue->size = queue->list->size;
}
void dequeue(queue_t *queue, void *data) {
  pop_back(queue->list, data);
  queue->size = queue->list->size;
}
void destruct_queue(queue_t *queue) {
  destruct_linked_list(queue->list);
  queue->size = 0;
}

bool_t is_empty_queue(const queue_t *queue) { return queue->size == 0; }

queue_t *create_queue(size_t size_of_data, compare_t compare,
                      destruct_t destruct, copy_t copy) {

  queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
  queue->list = create_linked_list(size_of_data, compare, destruct, copy);
  queue->size = 0;
  return queue;
}
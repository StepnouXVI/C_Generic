#include "advanced_functions.h"

bool_t contains_in_queue(const queue_t *queue, const void *data) {
  return contains_in_linked_list(queue->list, data);
}
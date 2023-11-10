#include "node_functions.h"
#include "../../support/validators.h"
#include "../helper/helper.h"
#include <stdlib.h>

static node_t *create_node(void) {
  node_t *node = malloc(sizeof(node_t));
  node->next = NULL;
  node->perv = NULL;
  return node;
}

static void destruct_node(node_t *node) {
  if (node == NULL)
    return;
  free(node);
}

node_t *create_node_and_copy_data(const copy_t copy, size_t size_of_data,
                                  const void *data) {
  node_t *node = create_node();
  node->data = (node_t *)malloc(size_of_data);

  if (MALLOC_FAILURE_CHECK(node->data)) {
    return NULL;
  }

  use_user_copy_or_default_memcpy(copy, size_of_data, data, node->data);
  return node;
}

void destruct_node_and_data(const destruct_t destruct, node_t *node) {
  use_user_destruct_or_default_free(destruct, node->data);
  destruct_node(node);
}

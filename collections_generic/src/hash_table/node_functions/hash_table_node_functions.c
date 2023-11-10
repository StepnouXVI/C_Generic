#include "node_functions.h"
#include "../../support/validators.h"
#include "../type_manager_functions/type_manager_functions.h"

#include <stdlib.h>

hash_table_node_t *create_hash_table_node(const type_manager_t *key_manager,
                                  const type_manager_t *value_manager,
                                  const void *key, const void *value) {

  if (NULL_ARGUMENT_CHECK(key_manager) || NULL_ARGUMENT_CHECK(value_manager) ||
      NULL_ARGUMENT_CHECK(key)) {
    return NULL;
  }

  hash_table_node_t *node = malloc(sizeof(hash_table_node_t));
  if (MALLOC_FAILURE_CHECK(node)) {
    return NULL;
  }

  node->key = malloc(key_manager->size_of_obj);
  if (MALLOC_FAILURE_CHECK(node->key)) {
    free(node);
    return NULL;
  }

  if (value != NULL) {
    node->value = malloc(value_manager->size_of_obj);
    if (MALLOC_FAILURE_CHECK(node->value)) {
      free(node->key);
      free(node);
      return NULL;
    }
  }

  use_user_copy_or_memcpy(key_manager, key, node->key);
  if (value != NULL) {
    use_user_copy_or_memcpy(value_manager, value, node->value);
  } else {
    node->value = NULL;
  }
  node->is_deleted = false;

  return node;
}

void destruct_hash_table_node(type_manager_t *key_manager,
                              type_manager_t *value_manager,
                              hash_table_node_t *node) {
  if (node == NULL)
    return;

  use_user_destruct_or_free(key_manager, node->key);
  use_user_destruct_or_free(value_manager, node->value);
  free(node);
}
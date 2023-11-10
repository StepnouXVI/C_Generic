#include "../../node_functions/node_functions.h"
#include "base_functions.h"
#include <stdlib.h>
#include "../../../support/validators.h"

void re_hash_hash_table(hash_table_t *table) {
  if (NULL_ARGUMENT_CHECK(table)) {
    return;
  }
  table->count_with_deleted = 0;
  table->count = 0;

  hash_table_node_t **new_nodes = (hash_table_node_t **)malloc(
      sizeof(hash_table_node_t *) * table->capacity);
  for (size_t i = 0; i < table->capacity; i++)
    new_nodes[i] = NULL;

  // swap node arrays
  hash_table_node_t **tmp = table->nodes;
  table->nodes = new_nodes;
  new_nodes = tmp;

  // Rehash elements
  for (size_t i = 0; i < table->capacity; i++) {
    if (new_nodes[i] && !new_nodes[i]->is_deleted) {
      add_to_hash_table(table, new_nodes[i]->key, new_nodes[i]->value);
    }
  }

  // destruct old nodes
  for (size_t i = 0; i < table->capacity; i++) {
    destruct_hash_table_node(&table->key_manager, &table->value_manager,
                             new_nodes[i]);
  }
  free(new_nodes);
}
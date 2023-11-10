#include "../../node_functions/node_functions.h"
#include "base_functions.h"
#include <stdlib.h>

void destruct_hash_table(hash_table_t *table) {
  if (table == NULL)
    return;

  for (size_t i = 0; i < table->capacity; i++) {
    destruct_hash_table_node(&table->key_manager, &table->value_manager,
                             table->nodes[i]);
  }
  free(table->nodes);
}

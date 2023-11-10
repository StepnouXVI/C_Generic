#include "../../../support/validators.h"
#include "base_functions.h"
#include <stdlib.h>
hash_table_t *create_hash_table(size_t key_size, copy_t key_copy,
                                destruct_t key_destruct, compare_t key_compare,
                                size_t value_size, copy_t value_copy,
                                destruct_t value_destruct,
                                compare_t value_compare) {

  if (NULL_ARGUMENT_CHECK(key_compare)) {
    return NULL;
  }

  hash_table_t *table = malloc(sizeof(hash_table_t));
  if (MALLOC_FAILURE_CHECK(table)) {
    return NULL;
  }

  table->capacity = DEFAULT_HASH_TABLE_SIZE;
  table->nodes = malloc(sizeof(hash_table_node_t *) * table->capacity);
  if (MALLOC_FAILURE_CHECK(table->nodes)) {
    free(table);
    return NULL;
  }

  for (size_t i = 0; i < DEFAULT_HASH_TABLE_SIZE; i++) {
    table->nodes[i] = NULL;
  }

  table->count = 0;
  table->count_with_deleted = 0;
  type_manager_t tmp1 = {key_size, .copy = key_copy, .destruct = key_destruct,
                         .compare = key_compare};
  table->key_manager = tmp1;
  type_manager_t tmp2 = {value_size, .copy = value_copy,
                         .destruct = value_destruct, .compare = value_compare};
  table->value_manager = tmp2;

  return table;
}
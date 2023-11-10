#include "../../../support/validators.h"
#include "../../node_functions/node_functions.h"
#include "../../type_manager_functions/type_manager_functions.h"
#include "../common/get_hash_code.h"
#include "base_functions.h"

bool_t add_to_hash_table(hash_table_t *table, const void *key, const void *data) {
  if (NULL_ARGUMENT_CHECK(table) || NULL_ARGUMENT_CHECK(key)) {
    return false;
  }

  if (table->count > table->capacity * REHASH_THRESHOLD) {
    resize_hash_table(table);
  } else if (table->count_with_deleted > table->count * RESIZE_FACTOR) {
    re_hash_hash_table(table);
  }

  size_t hash1 = get_hash_code_1(table, key);
  size_t hash2 = get_hash_code_2(table, key);

  size_t i = 0;
  size_t index_of_first_deleted;
  bool_t find_deleted = false;
  while (table->nodes[hash1] != NULL && i < table->capacity) {
    if (table->key_manager.compare(table->nodes[hash1]->key, key) == 0 &&
        !table->nodes[hash1]->is_deleted)
      return false;

    if (table->nodes[hash1]->is_deleted && !find_deleted) {
      index_of_first_deleted = hash1;
      find_deleted = true;
    }

    hash1 = (hash1 + hash2) % table->capacity;
    i++;
  }

  if (!find_deleted) {
    table->nodes[hash1] = create_hash_table_node(
        &table->key_manager, &table->value_manager, key, data);
    table->count_with_deleted++;
  } else {
    use_user_copy_or_memcpy(&table->value_manager, data,
                            table->nodes[index_of_first_deleted]->value);
    table->nodes[index_of_first_deleted]->is_deleted = false;
  }
  table->count++;
  return true;
}
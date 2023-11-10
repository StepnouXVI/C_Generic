
#include "../common/get_hash_code.h"
#include "base_functions.h"

bool_t contains_key(const hash_table_t *table, const void *key) {
  size_t hash1 = get_hash_code_1(table, key);
  size_t hash2 = get_hash_code_2(table, key);

  for (size_t i = 0; table->nodes[hash1] != NULL && i < table->capacity; i++) {
    if (table->key_manager.compare(table->nodes[hash1]->key, key) == 0 &&
        !table->nodes[hash1]->is_deleted)
      return true;
    hash1 = (hash1 + hash2) % table->capacity;
  }
  return false;
}
#include "../../../support/validators.h"
#include "../common/get_hash_code.h"
#include "base_functions.h"

bool_t remove_from_hash_table(hash_table_t *table, const void *key) {
  if (NULL_ARGUMENT_CHECK(table) || NULL_ARGUMENT_CHECK(key)) {
    return false;
  }
  size_t hash1 = get_hash_code_1(table, key);
  size_t hash2 = get_hash_code_2(table, key);
  size_t i = 0;

  while (table->nodes[hash1] != NULL && i < table->capacity) {
    if (table->key_manager.compare(table->nodes[hash1]->key, key) == 0 &&
        !table->nodes[hash1]->is_deleted) {
      table->nodes[hash1]->is_deleted = true;
      table->count--;
      return true;
    }

    hash1 = (hash1 + hash2) % table->capacity;
    i++;
  }
  return false;
}
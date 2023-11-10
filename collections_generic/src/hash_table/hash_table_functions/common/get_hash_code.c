#include "get_hash_code.h"

#include "../../../support/validators.h"
#include "hash.h"
static size_t get_user_hash_code_or_default(const hash_table_t *table,
                                            size_t key_gen, const void *key) {
  if (NULL_ARGUMENT_CHECK(key) || NULL_ARGUMENT_CHECK(table)) {
    return 0;
  }

  size_t hash = 0;

  if (table->get_hash_code != NULL) {
    hash = table->get_hash_code(table->capacity, key_gen, key);
  } else {
    hash = get_hash_code_default(table->capacity, key_gen, key,
                                 table->key_manager.size_of_obj);
  }
  return hash;
}

size_t get_hash_code_1(const hash_table_t *table, const void *key) {
  return get_user_hash_code_or_default(table, table->capacity + 1, key);
}
size_t get_hash_code_2(const hash_table_t *table, const void *key) {
  return get_user_hash_code_or_default(table, table->capacity - 1, key);
}
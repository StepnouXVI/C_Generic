#include "../../../support/validators.h"
#include "../../type_manager_functions/type_manager_functions.h"
#include "../common/get_hash_code.h"
#include "base_functions.h"

bool_t change_in_hash_table(hash_table_t *table, const void *key,
                          const void *data) {

  if (NULL_ARGUMENT_CHECK(table) || NULL_ARGUMENT_CHECK(key)) {
    return false;
  }

  size_t hash1 = get_hash_code_1(table, key);
  size_t hash2 = get_hash_code_2(table, key);

  for (size_t i = 0; table->nodes[hash1] != NULL && i < table->capacity; i++) {
    if (table->key_manager.compare(table->nodes[hash1]->key, key) == 0 &&
        !table->nodes[hash1]->is_deleted) {
      use_user_copy_or_memcpy(&table->value_manager, data,
                              table->nodes[hash1]->value);
      return true;
    }
    hash1 = (hash1 + hash2) % table->capacity;
  }
  return false;
}
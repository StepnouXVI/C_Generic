#include "../src/hash_table/hash_table.h"
#include <stdio.h>


int compare_ints(const int *a, const int *b) { return *a - *b; }

int main(void) {
  hash_table_t *table =
      create_hash_table(sizeof(int), (NULL), (NULL), (compare_t)(compare_ints),
                        sizeof(float), NULL, NULL, NULL);

  printf("[table]%p\n", (table));

  int key = 42;
  float value = -420.2;

  bool_t result = add_to_hash_table(table, &key, &value);
  printf("[result]%d == %d\n", result, true);

  bool_t exists = contains_key(table, &key);
  printf("[result]%d == %d\n", exists, true);

  float retrieved_value;
  bool_t get_result = get_from_hash_table(table, &key, &retrieved_value);
  printf("[result]%d == %d\n", get_result, true);
  printf("[result]%f == %f\n", retrieved_value, value);

  // Destroy the hash table
  destruct_hash_table(table);
}

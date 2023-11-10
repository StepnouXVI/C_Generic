#include "../types/user_type_string/string.h"
#include "hash_table_tests.h"

START_TEST(test_add_to_hash_table_existing_key) {
  hash_table_t *table = create_hash_table(
      sizeof(string_t), (copy_t)copy_string, (destruct_t)destroy_string,
      (compare_t)compare_strings, sizeof(int), NULL, NULL, NULL);

  table->get_hash_code = (get_hash_code_t)get_hash_code_string;

  ck_assert_ptr_nonnull(table);

  string_t *key = create_string("example");
  int value = 42;

  bool_t result = add_to_hash_table(table, key, &value);
  ck_assert_int_eq(result, true);

  bool_t exists = contains_key(table, key);
  ck_assert_int_eq(exists, true);

  int retrieved_value;
  bool_t get_result = get_from_hash_table(table, &key, &retrieved_value);
  ck_assert_int_eq(get_result, true);
  ck_assert_int_eq(retrieved_value, value);

  // Destroy the hash table
  destruct_hash_table(table);
}END_TEST

START_TEST(test_add_to_hash_table_duplicate_key)
{
  // Create a hash table
  hash_table_t *table = create_hash_table(
    sizeof(string_t), (copy_t)copy_string, (destruct_t)destroy_string,
    (compare_t)compare_strings, sizeof(int), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and initial values
  string_t *key = create_string("example");
  int initial_value1 = 42;
  int initial_value2 = 99;

  // Add the key-value pair to the hash table
  bool_t result1 = add_to_hash_table(table, key, &initial_value1);
  ck_assert_int_eq(true, result1);

  // Try to add a duplicate key-value pair to the hash table
  bool_t result2 = add_to_hash_table(table, key, &initial_value2);
  ck_assert_int_eq(false, result2);

  // Get the value associated with the key
  int retrieved_value;
  bool_t get_result = get_from_hash_table(table, key, &retrieved_value);
  ck_assert_int_eq(true, get_result);
  ck_assert_int_eq(initial_value1, retrieved_value);

  // Destroy the hash table and key
  destruct_hash_table(table);
  destroy_string(key);
}
END_TEST


START_TEST(test_contains_key)
{
  // Create a hash table
  hash_table_t *table = create_hash_table(
      sizeof(string_t), (copy_t)copy_string, (destruct_t)destroy_string,
      (compare_t)compare_strings, sizeof(int), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and value
  string_t *key = create_string("example");
  int value = 42;

  // Add the key-value pair to the hash table
  bool_t result = add_to_hash_table(table, key, &value);
  ck_assert_int_eq(true, result);

  // Check if the key exists in the hash table
  bool_t exists = contains_key(table, key);
  ck_assert_int_eq(true, exists);

  // Destroy the hash table
  destruct_hash_table(table);
  destroy_string(key);
}
END_TEST

START_TEST(test_contains_key_2_keys)
{
  // Create a hash table
  hash_table_t *table = create_hash_table(
    sizeof(string_t), (copy_t)copy_string, (destruct_t)destroy_string,
    (compare_t)compare_strings, sizeof(int), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and value
  string_t *key1 = create_string("example");
  int value1 = 42;

  // Add the key-value pair to the hash table
  bool_t result1 = add_to_hash_table(table, key1, &value1);
  ck_assert_int_eq(true, result1);

  // Check if the key exists in the hash table
  bool_t exists1 = contains_key(table, key1);
  ck_assert_int_eq(true, exists1);

  // Define another key and value
  string_t *key2 = create_string("another_example");
  int value2 = 99;

  // Check if the second key exists in the hash table
  bool_t exists2 = contains_key(table, key2);
  ck_assert_int_eq(false, exists2);

  // Add the second key-value pair to the hash table
  bool_t result2 = add_to_hash_table(table, key2, &value2);
  ck_assert_int_eq(true, result2);

  // Check if the second key now exists in the hash table
  bool_t exists3 = contains_key(table, key2);
  ck_assert_int_eq(true, exists3);

  // Destroy the hash table and keys
  destruct_hash_table(table);
    destroy_string(key1);
    destroy_string(key2);
}
END_TEST


START_TEST(test_change_in_hash_table)
{
  // Create a hash table
  hash_table_t *table = create_hash_table(
      sizeof(string_t), (copy_t)copy_string, (destruct_t)destroy_string,
      (compare_t)compare_strings, sizeof(int), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and value
  string_t *key = create_string("example");
  int value = 42;

  // Add the key-value pair to the hash table
  bool_t result = add_to_hash_table(table, key, &value);
  ck_assert_int_eq(true, result);

  // Change the value associated with the key
  int new_value = 99;
  bool_t change_result = change_in_hash_table(table, key, &new_value);
  ck_assert_int_eq(true, change_result);

  // Get the updated value associated with the key
  int retrieved_value;
  bool_t get_result = get_from_hash_table(table, key, &retrieved_value);
  ck_assert_int_eq(true, get_result);
  ck_assert_int_eq(retrieved_value, new_value);

  // Destroy the hash table
  destruct_hash_table(table);
  destroy_string(key);
}
END_TEST

START_TEST(test_change_in_hash_table_not_exist_key)
{
  // Create a hash table
  hash_table_t *table = create_hash_table(
    sizeof(string_t), (copy_t)copy_string, (destruct_t)destroy_string,
    (compare_t)compare_strings, sizeof(int), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and initial value
  string_t *key = create_string("example");
  int initial_value = 42;

  // Add the key-value pair to the hash table
  bool_t result = add_to_hash_table(table, key, &initial_value);
  ck_assert_int_eq(true, result);

  // Try to change the value associated with a non-existing key
  string_t *non_existing_key = create_string("non_existing");
  int new_value = 99;
  bool_t change_result = change_in_hash_table(table, non_existing_key, &new_value);
  ck_assert_int_eq(false, change_result);

  // Get the original value associated with the key
  int retrieved_value;
  bool_t get_result = get_from_hash_table(table, key, &retrieved_value);
  ck_assert_int_eq(true, get_result);
  ck_assert_int_eq(initial_value, retrieved_value);

  // Change the value associated with the key
  int updated_value = 77;
  change_result = change_in_hash_table(table, key, &updated_value);
  ck_assert_int_eq(true, change_result);

  // Get the updated value associated with the key
  get_result = get_from_hash_table(table, key, &retrieved_value);
  ck_assert_int_eq(true, get_result);
  ck_assert_int_eq(updated_value, retrieved_value);

  // Destroy the hash table and keys
  destruct_hash_table(table);
  destroy_string(key);
    destroy_string(non_existing_key);
}
END_TEST


START_TEST(test_get_from_hash_table)
{
  // Create a hash table
  hash_table_t *table = create_hash_table(
      sizeof(string_t), (copy_t)copy_string, (destruct_t)destroy_string,
      (compare_t)compare_strings, sizeof(int), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and value
  string_t *key = create_string("example");
  int value = 42;

  // Add the key-value pair to the hash table
  bool_t result = add_to_hash_table(table, key, &value);
  ck_assert_int_eq(true, result);

  // Get the value associated with the key
  int retrieved_value;
  bool_t get_result = get_from_hash_table(table, key, &retrieved_value);
  ck_assert_int_eq(true, get_result);
  ck_assert_int_eq(retrieved_value, value);

  // Destroy the hash table
  destruct_hash_table(table);
  destroy_string(key);
}
END_TEST


START_TEST(test_get_from_hash_table_non_existing_key)
{
  // Create a hash table
  hash_table_t *table = create_hash_table(
    sizeof(string_t), (copy_t)copy_string, (destruct_t)destroy_string,
    (compare_t)compare_strings, sizeof(int), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and initial value
  string_t *key = create_string("example");
  int initial_value = 42;

  // Add the key-value pair to the hash table
  bool_t result = add_to_hash_table(table, key, &initial_value);
  ck_assert_int_eq(true, result);

  // Try to get the value associated with a non-existing key
  string_t *non_existing_key = create_string("non_existing");
  int retrieved_value;
  bool_t get_result = get_from_hash_table(table, non_existing_key, &retrieved_value);
  ck_assert_int_eq(false, get_result);

  // Destroy the hash table and keys
  destruct_hash_table(table);
  destroy_string(key);
    destroy_string(non_existing_key);
}
END_TEST

START_TEST(test_remove_from_hash_table_existing_key)
{
  // Create a hash table
  hash_table_t *table = create_hash_table(
    sizeof(string_t), (copy_t)copy_string, (destruct_t)destroy_string,
    (compare_t)compare_strings, sizeof(int), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and initial value
  string_t *key = create_string("example");
  int initial_value = 42;

  // Add the key-value pair to the hash table
  bool_t result = add_to_hash_table(table, key, &initial_value);
  ck_assert_int_eq(true, result);

  // Remove the key-value pair from the hash table
  bool_t remove_result = remove_from_hash_table(table, key);
  ck_assert_int_eq(true, remove_result);

  // Check if the key still exists in the hash table
  bool_t exists = contains_key(table, key);
  ck_assert_int_eq(false, exists);

  // Destroy the hash table and key
  destruct_hash_table(table);
  destroy_string(key);
}
END_TEST

START_TEST(test_remove_from_hash_table_non_existing_key)
{
  // Create a hash table
  hash_table_t *table = create_hash_table(
    sizeof(string_t), (copy_t)copy_string, (destruct_t)destroy_string,
    (compare_t)compare_strings, sizeof(int), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and initial value
  string_t *key = create_string("example");
  int initial_value = 42;

  // Add the key-value pair to the hash table
  bool_t result = add_to_hash_table(table, key, &initial_value);
  ck_assert_int_eq(true, result);

  // Try to remove a non-existing key from the hash table
  string_t *non_existing_key = create_string("non_existing");
  bool_t remove_result = remove_from_hash_table(table, non_existing_key);
  ck_assert_int_eq(false, remove_result);

  // Check if the original key still exists in the hash table
  bool_t exists = contains_key(table, key);
  ck_assert_int_eq(true, exists);

  // Destroy the hash table and keys
  destruct_hash_table(table);
  destroy_string(key);
    destroy_string(non_existing_key);
}
END_TEST

Suite *create_test_suite_hash_table_str_key_int_value(void) {
  Suite *suite = suite_create("StringKeyIntValueTests");

  TCase *tc_add_to_hash_table = tcase_create("AddToHashTable");
  tcase_add_test(tc_add_to_hash_table, test_add_to_hash_table_existing_key);
  tcase_add_test(tc_add_to_hash_table, test_add_to_hash_table_duplicate_key);
  suite_add_tcase(suite, tc_add_to_hash_table);

  TCase *tc_change_in_hash_table = tcase_create("ChangeInHashTable");
  tcase_add_test(tc_change_in_hash_table, test_change_in_hash_table);
  tcase_add_test(tc_change_in_hash_table, test_change_in_hash_table_not_exist_key);

  suite_add_tcase(suite, tc_change_in_hash_table);

  TCase *tc_get_from_hash_table = tcase_create("GetFromHashTable");
  tcase_add_test(tc_get_from_hash_table, test_get_from_hash_table);
  tcase_add_test(tc_get_from_hash_table, test_get_from_hash_table_non_existing_key);
  suite_add_tcase(suite, tc_get_from_hash_table);

  TCase *tc_remove_from_hash_table = tcase_create("RemoveFromHashTable");
  tcase_add_test(tc_remove_from_hash_table, test_remove_from_hash_table_existing_key);
  tcase_add_test(tc_remove_from_hash_table, test_remove_from_hash_table_non_existing_key);
  suite_add_tcase(suite, tc_remove_from_hash_table);

  TCase *tc_contains_key = tcase_create("ContainsKey");
  tcase_add_test(tc_contains_key, test_contains_key);
  tcase_add_test(tc_contains_key, test_contains_key_2_keys);
  suite_add_tcase(suite, tc_contains_key);

  return suite;
}

#include "../types/int/int.h"
#include "hash_table_tests.h"
#define ACCURACY 1e-6

START_TEST(test_add_to_hash_table_existing_key) {
  hash_table_t *table =
      create_hash_table(sizeof(int), (NULL), (NULL), (compare_t)(compare_ints),
                        sizeof(float), NULL, NULL, NULL);

  ck_assert(table != NULL);

  int key = 42;
  float value = -420.2;

  bool_t result = add_to_hash_table(table, &key, &value);
  ck_assert_int_eq(result, true);

  bool_t exists = contains_key(table, &key);
  ck_assert_int_eq(exists, true);

  float retrieved_value;
  bool_t get_result = get_from_hash_table(table, &key, &retrieved_value);
  ck_assert_int_eq(get_result, true);
  ck_assert_float_eq_tol(retrieved_value, value, ACCURACY);

  // Destroy the hash table
  destruct_hash_table(table);
}
END_TEST

START_TEST(test_add_to_hash_table_duplicate_key) {
  // Create a hash table
  hash_table_t *table =
      create_hash_table(sizeof(int), NULL, NULL, (compare_t)compare_ints,
                        sizeof(float), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and initial values
  int key = 42;
  float initial_value1 = 3.14;
  float initial_value2 = 2.71;

  // Add the key-value pair to the hash table
  bool_t result1 = add_to_hash_table(table, &key, &initial_value1);
  ck_assert_int_eq(true, result1);

  // Try to add a duplicate key-value pair to the hash table
  bool_t result2 = add_to_hash_table(table, &key, &initial_value2);
  ck_assert_int_eq(false, result2);

  // Destroy the hash table
  destruct_hash_table(table);
}
END_TEST

START_TEST(test_get_from_hash_table_existing_key) {
  // Create a hash table
  hash_table_t *table =
      create_hash_table(sizeof(int), NULL, NULL, (compare_t)compare_ints,
                        sizeof(float), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and initial value
  int key = 42;
  float initial_value = 3.14;

  // Add the key-value pair to the hash table
  bool_t result = add_to_hash_table(table, &key, &initial_value);
  ck_assert_int_eq(true, result);

  // Retrieve the value associated with the key
  float retrieved_value;
  bool_t get_result = get_from_hash_table(table, &key, &retrieved_value);
  ck_assert_int_eq(true, get_result);
  ck_assert_float_eq(initial_value, retrieved_value);

  // Destroy the hash table
  destruct_hash_table(table);
}
END_TEST

START_TEST(test_get_from_hash_table_non_existing_key) {
  // Create a hash table
  hash_table_t *table =
      create_hash_table(sizeof(int), NULL, NULL, (compare_t)compare_ints,
                        sizeof(float), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and initial value
  int key = 42;

  // Add a different key-value pair to the hash table
  int different_key = 99;
  float different_value = 2.71;
  bool_t add_result =
      add_to_hash_table(table, &different_key, &different_value);
  ck_assert_int_eq(true, add_result);

  // Retrieve the value associated with the non-existing key
  float retrieved_value;
  bool_t get_result = get_from_hash_table(table, &key, &retrieved_value);
  ck_assert_int_eq(false, get_result);

  // Destroy the hash table
  destruct_hash_table(table);
}
END_TEST

START_TEST(test_change_in_hash_table) {
  // Create a hash table
  hash_table_t *table =
      create_hash_table(sizeof(int), NULL, NULL, (compare_t)compare_ints,
                        sizeof(float), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and initial value
  int key = 42;
  float initial_value = 3.14;

  // Add the key-value pair to the hash table
  bool_t add_result = add_to_hash_table(table, &key, &initial_value);
  ck_assert_int_eq(true, add_result);

  // Change the value associated with the key
  float new_value = 2.71;
  bool_t change_result = change_in_hash_table(table, &key, &new_value);
  ck_assert_int_eq(true, change_result);

  // Retrieve the updated value associated with the key
  float retrieved_value;
  bool_t get_result = get_from_hash_table(table, &key, &retrieved_value);
  ck_assert_int_eq(true, get_result);
  ck_assert_float_eq(new_value, retrieved_value);

  // Destroy the hash table
  destruct_hash_table(table);
}
END_TEST

START_TEST(test_change_in_hash_table_non_existing_key) {
  // Create a hash table
  hash_table_t *table =
      create_hash_table(sizeof(int), NULL, NULL, (compare_t)compare_ints,
                        sizeof(float), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and initial value
  int key = 42;

  // Add a different key-value pair to the hash table
  int different_key = 99;
  float different_value = 2.71;
  bool_t add_result =
      add_to_hash_table(table, &different_key, &different_value);
  ck_assert_int_eq(true, add_result);

  // Attempt to change the value associated with the non-existing key
  float new_value = 1.23;
  bool_t change_result = change_in_hash_table(table, &key, &new_value);
  ck_assert_int_eq(false, change_result);

  // Destroy the hash table
  destruct_hash_table(table);
}
END_TEST

START_TEST(test_remove_from_hash_table) {
  // Create a hash table
  hash_table_t *table =
      create_hash_table(sizeof(int), NULL, NULL, (compare_t)compare_ints,
                        sizeof(float), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and value
  int key = 42;
  float value = 3.14;

  // Add the key-value pair to the hash table
  bool_t add_result = add_to_hash_table(table, &key, &value);
  ck_assert_int_eq(true, add_result);

  // Remove the key-value pair from the hash table
  bool_t remove_result = remove_from_hash_table(table, &key);
  ck_assert_int_eq(true, remove_result);

  // Check that the key is no longer in the hash table
  float retrieved_value;
  bool_t get_result = get_from_hash_table(table, &key, &retrieved_value);
  ck_assert_int_eq(false, get_result);

  // Destroy the hash table
  destruct_hash_table(table);
}
END_TEST

START_TEST(test_remove_from_hash_table_non_existing_key) {
  // Create a hash table
  hash_table_t *table =
      create_hash_table(sizeof(int), NULL, NULL, (compare_t)compare_ints,
                        sizeof(float), NULL, NULL, NULL);
  ck_assert_ptr_nonnull(table);

  // Define the key and value
  int key = 42;

  // Add a different key-value pair to the hash table
  int different_key = 99;
  float different_value = 2.71;
  bool_t add_result =
      add_to_hash_table(table, &different_key, &different_value);
  ck_assert_int_eq(true, add_result);

  // Attempt to remove the non-existing key-value pair from the hash table
  bool_t remove_result = remove_from_hash_table(table, &key);
  ck_assert_int_eq(false, remove_result);

  // Destroy the hash table
  destruct_hash_table(table);
}
END_TEST

Suite *create_test_suite_hash_table_int_key_float_value(void) {
  Suite *suite = suite_create("Hash Table Tests");

  // Add the test cases to the suite
  TCase *tcase_add = tcase_create("Add in hash table");
  tcase_add_test(tcase_add, test_add_to_hash_table_existing_key);
  tcase_add_test(tcase_add, test_add_to_hash_table_duplicate_key);
  suite_add_tcase(suite, tcase_add);

  TCase *tcase_get_value = tcase_create("Get Value from Hash Table");
  tcase_add_test(tcase_get_value, test_get_from_hash_table_existing_key);
  tcase_add_test(tcase_get_value, test_get_from_hash_table_non_existing_key);
  suite_add_tcase(suite, tcase_get_value);

  TCase *tcase_change_value = tcase_create("Change Value in Hash Table");
  tcase_add_test(tcase_change_value, test_change_in_hash_table);
  tcase_add_test(tcase_change_value,
                 test_change_in_hash_table_non_existing_key);
  suite_add_tcase(suite, tcase_change_value);

  TCase *tcase_remove_value = tcase_create("Remove Value from Hash Table");
  tcase_add_test(tcase_remove_value, test_remove_from_hash_table);
  tcase_add_test(tcase_remove_value,
                 test_remove_from_hash_table_non_existing_key);
  suite_add_tcase(suite, tcase_remove_value);

  return suite;
}

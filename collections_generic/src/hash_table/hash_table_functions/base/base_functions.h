#ifndef BASE_FUNCTIONS_HASH_TABLE_H
#define BASE_FUNCTIONS_HASH_TABLE_H

#include "../../types/hash_table.h"

/**
 * Creates a new hash table with the specified key and value sizes, key and
 * value copy functions, key and value destruct functions, and key and value
 * comparison functions.
 *
 * @param key_size size of the keys in the hash table
 * @param key_copy function for copying the keys
 * @param key_destruct function for destroying the keys
 * @param key_compare function for comparing the keys
 * @param value_size size of the values in the hash table
 * @param value_copy function for copying the values
 * @param value_destruct function for destroying the values
 * @param value_compare function for comparing the values
 *
 * @return a pointer to the newly created hash table
 *
 * @note Value_compare can be NULL.
 * @note If you do not set the destruct and copy functions, `free` and `memcpy`
 * will be used by default.
 */
hash_table_t *create_hash_table(size_t key_size, copy_t key_copy,
                                destruct_t key_destruct, compare_t key_compare,
                                size_t value_size, copy_t value_copy,
                                destruct_t value_destruct,
                                compare_t value_compare);

/**
 * Deallocates all memory used by the given hash table.
 *
 * @param table Pointer to the hash table to be deallocated.
 */
void destruct_hash_table(hash_table_t *table);

bool_t add_to_hash_table(hash_table_t *table, const void *key, const void *data);

/**
 * @brief Rehashes the given hash table
 *
 * @param table Pointer to the hash table to rehash
 *
 * @details This function rehashes the given hash table to improve its
 * performance. It resets the number of items in the hash table, creates a new
 * array of nodes, swaps the old node array with the new one, rehashes the
 * elements, destructs the old nodes, and frees the memory used by the old node
 * array. The hash table's destruct functions are used to destruct the old
 * nodes.
 */
void re_hash_hash_table(hash_table_t *table);

/**
 * @brief Resizes a hash table to twice its current capacity.
 *
 * This function doubles the capacity of the hash table, creates a new array of
 * nodes with the new capacity, and rehashes all of the existing key-value
 * pairs into the new array. The old array is then destroyed and the hash table
 * is updated to use the new array.
 *
 * @param table A pointer to the hash table to resize.
 */
void resize_hash_table(hash_table_t *table);

/**
 * @brief Checks if a key exists in a given hash table.
 *
 * @param ht A pointer to the hash table to search in.
 * @param key A pointer to the key to search for.
 * @return True if the key is found in the hash table, False otherwise.
 */
bool_t contains_key(const hash_table_t *table, const void *key);

bool_t change_in_hash_table(hash_table_t *table, const void *key,
                          const void *data);
/**
 * @brief Gets the value associated with a key in a hash table.
 *
 * This function searches for the given key in the hash table and, if it is
 * found, copies the value associated with it into the given data pointer. If
 * the key is not found, the function returns false and the data pointer is not
 * modified.
 *
 * @param table A pointer to the hash table to search in.
 * @param key A pointer to the key to search for.
 * @param data A pointer to a buffer to receive the value associated with the
 * key.
 * @return True if the key was found and the value was copied, false otherwise.
 */
bool_t get_from_hash_table(const hash_table_t *table, const void *key, void *data);

/**
 * @brief remove_from_hash_tables a key-value pair from a hash table.
 *
 * This function searches for the given key in the hash table and, if it is
 * found, marks the corresponding node as deleted and decrements the count of
 * the hash table. If the key is not found, the function returns false.
 *
 * @param table A pointer to the hash table to remove_from_hash_table from.
 * @param key A pointer to the key to remove_from_hash_table.
 * @return True if the key was found and remove_from_hash_tabled, false
 * otherwise.
 */
bool_t remove_from_hash_table(hash_table_t *ht, const void *key);
#endif
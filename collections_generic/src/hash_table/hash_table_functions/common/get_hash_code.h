#ifndef GET_HASH_CODE_OR_USE_DEFAULT_H
#define GET_HASH_CODE_OR_USE_DEFAULT_H
#include "../../types/hash_table.h"
/**
 * @brief Computes a hash function for a given key and hash table capacity.
 *
 * @param capacity The capacity of the hash table.
 * @param get_size_of_key Pointer to a function that returns the size of the
 * key.
 * @param key Pointer to the key.
 * @return The computed hash value.
 *
 * The function computes a hash function for a given key and hash table
 * capacity. This function simply calls Hash() with the appropriate arguments.
 *
 * @note The returned value may be greater than the hash table capacity.
 *
 */
size_t get_hash_code_1(const hash_table_t *table, const void *key);

/**
 * @brief Computes a hash function for a given key and hash table capacity.
 *
 * @param capacity The capacity of the hash table.
 * @param get_size_of_key Pointer to a function that returns the size of the
 * key.
 * @param key Pointer to the key.
 * @return The computed hash value.
 *
 * The function computes a hash function for a given key and hash table
 * capacity. This function simply calls Hash() with the appropriate arguments.
 *
 * @note The returned value may be greater than the hash table capacity.
 *
 */
size_t get_hash_code_2(const hash_table_t *table, const void *key);

#endif
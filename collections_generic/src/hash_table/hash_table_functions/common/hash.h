#ifndef HASH_H
#define HASH_H
#include <stddef.h>
/**
 * @brief Computes a hash value for a given key, key generator, and hash table
 * capacity.
 *
 * @param capacity The capacity of the hash table.
 * @param keygen The key generator value.
 * @param key Pointer to the key.
 * @param get_size_of_data Pointer to a function that returns the size of the data.
 * @return The computed hash value.
 *
 * The function computes a hash value for a given key, key generator value, and
 * hash table capacity. The hash value is computed using a variation of the djb2
 * algorithm.
 *
 * @see http://www.cse.yorku.ca/~oz/hash.html
 *
 * @note The returned value may be greater than the hash table capacity.
 */
size_t get_hash_code_default(size_t capacity, size_t key_gen, const void* key, size_t key_size);
#define DEFAULT_GET_HASH_CODE get_hash_code_default

#endif
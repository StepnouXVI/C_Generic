#ifndef HASH_TABLE_T_H
#define HASH_TABLE_T_H

#include "hash_table_node.h"
#include "type_manager.h"

#define DEFAULT_HASH_TABLE_SIZE 100
#define REHASH_THRESHOLD 0.75f

#define RESIZE_FACTOR 2

/**
 * @brief A hash table.
 *
 * @details This struct represents a hash table.
 *
 * @param capacity Maximum number of elements in the table.
 * @param count Number of elements in the table (excluding deleted nodes).
 * @param count_with_deleted Number of elements in the table (including deleted nodes).
 * @param nodes Array of pointers to nodes.
 * @param key_manager A type manager for the keys in the hash table.
 * @param value_manager A type manager for the values in the hash table.
 * @param get_hash_code Function pointer to get hash codes.
 */
typedef struct hash_table_t {
  size_t capacity; /**< Maximum number of elements in the table. */
  size_t count; /**< Number of elements in the table (excluding deleted nodes). */
  size_t count_with_deleted; /**< Number of elements in the table (including deleted nodes). */
  hash_table_node_t **nodes; /**< Array of pointers to nodes. */
  type_manager_t key_manager; /**< A type manager for the keys in the hash table. */
  type_manager_t value_manager; /**< A type manager for the values in the hash table. */

  get_hash_code_t get_hash_code; /**< Function pointer to get hash codes. */
} hash_table_t;


#endif
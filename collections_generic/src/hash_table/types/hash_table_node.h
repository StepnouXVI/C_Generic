#ifndef HASH_TABLE_NODE_H
#define HASH_TABLE_NODE_H
#include "../../types/bool_t.h"

/**
 * @brief A node in a hash table.
 *
 * @details This struct represents a node in a hash table. It contains a key,
 * a value, and a flag indicating whether the node has been marked as deleted.
 */
typedef struct hash_table_node_t {
  void *key;      /**< Pointer to the key stored in the node. */
  void *value;    /**< Pointer to the value stored in the node. */
  bool_t is_deleted; /**< Flag indicating whether the node has been marked as
                     deleted. */
} hash_table_node_t;

#endif
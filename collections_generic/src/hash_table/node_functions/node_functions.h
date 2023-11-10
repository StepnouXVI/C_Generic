#ifndef NODE_FUNCTIONS_H
#define NODE_FUNCTIONS_H

#include "../types/hash_table_node.h"
#include "../types/type_manager.h"
hash_table_node_t *create_hash_table_node(const type_manager_t *key_manager,
                                  const type_manager_t *value_manager,
                                  const void *key, const void *value);

void destruct_hash_table_node(type_manager_t *key_manager,
                              type_manager_t *value_manager,
                              hash_table_node_t *node);
#endif
#ifndef NODE_T_H
#define NODE_T_H

#include "../../types/bool_t.h"
/**
 * @brief A node in a linked list.
 *
 * @details This structure represents a node in a linked list, and contains
 * pointers to the next and previous nodes in the list, as well as a pointer to
 * the data stored in the node. The next and previous node pointers are used to
 * traverse the list, and the data pointer is used to access the data stored in
 * the node.
 */
typedef struct node_t {
  struct node_t *next; /**< Pointer to the next node in the linked list. */
  struct node_t *perv; /**< Pointer to the previous node in the linked list. */
  void *data;          /**< Pointer to the data stored in the node. */
} node_t;

#endif
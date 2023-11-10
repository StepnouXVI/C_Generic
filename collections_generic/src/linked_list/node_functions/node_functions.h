#ifndef NODE_FUNCTIONS_H
#define NODE_FUNCTIONS_H

#include "../types/node_t.h"
#include "../../types/functions.h"


node_t* create_node_and_copy_data(const copy_t copy, size_t size_of_data, const void* data);
void destruct_node_and_data(const destruct_t destruct, node_t* node);


#endif
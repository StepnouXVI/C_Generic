#include "hash.h"
#include <stdint.h>

size_t get_hash_code_default(size_t capacity, size_t key_gen, const void* key, size_t key_size)
{
  size_t hash = 0;
  const int8_t* data_bytes = (const int8_t*)key;
  for (size_t i = 0; i < key_size; i++)
    hash = (hash * key_gen + data_bytes[i]) % capacity;
  hash = (hash * 2 + 1) % capacity;
  return hash; 
}
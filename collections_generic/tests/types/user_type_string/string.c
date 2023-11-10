#include "string.h"
#include <stdlib.h>
#include <string.h>

string_t *create_string(const char *string) {
  string_t *res = (string_t *)malloc(sizeof(string_t));
  res->string = (char *)malloc(strlen(string) + 1);
  strcpy(res->string, string);
  res->size = strlen(string) + 1;
  return res;
}

void destroy_string(string_t *string) {
  if (string == NULL)
    return;
  if (string->string != NULL)
    free(string->string);
  free(string);
}

void copy_string(const string_t *src, string_t *dest) {
  if (dest == NULL || src == NULL)
    return;

  dest->string = (char *)malloc(src->size);
  strcpy(dest->string, src->string);
  dest->size = src->size;
}

int compare_strings(const string_t *a, const string_t *b) {
  return strcmp(a->string, b->string);
}

static char *make_random_string(void) {
  size_t size = random() + 1;
  char *res = (char *)malloc(size);
  for (size_t i = 0; i < size; i++)
    res[i] = random() % 127;
  res[size - 1] = '\0';
  return res;
}

string_t *make_random_string_array(size_t size) {
  string_t *array = (string_t *)malloc(size * sizeof(string_t));
  for (size_t i = 0; i < size; i++) {
    char *temp = make_random_string();
    array[i].string = temp;
    array[i].size = strlen(temp) + 1;
  }
  return array;
}

void destruct_string_array(string_t *array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    destroy_string(&array[i]);
  }
  free(array);
}

size_t get_hash_code_string(size_t capacity, size_t key_gen, const string_t* key)
{
  size_t key_size = key->size - 1;
  size_t hash = 0;
  for (size_t i = 0; i < key_size; i++)
    hash = (hash * key_gen + key->string[i]) % capacity;
  hash = (hash * 2 + 1) % capacity;
  return hash; 
}
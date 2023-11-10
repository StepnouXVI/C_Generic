#include "../../string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void destruct_string(string_t *string) {
  if (string == NULL)
    return;

  if (string->string != NULL)
    free(string->string);

  free(string);
}

string_t* create_string(const char* src)
{
  string_t* res = malloc(sizeof(string_t));
  res->size = strlen(src) + 1;
  res->string = malloc(sizeof(char) * res->size);
  strcpy(res->string, src);
  return res;
}

string_t *create_clear_string(void) {
  string_t *string = malloc(sizeof(string_t));
  string->size = 1;
  string->string = malloc(sizeof(char));
  string->string[0] = '\0';
  return string;
}

void add_char(string_t *string, char symbol) {
  string->size++;
  string->string = (char *)realloc(string->string, string->size);
  string->string[string->size - 2] = symbol;
  string->string[string->size - 1] = '\0';
}

string_t *read_string_without_specified_symbols(FILE *file,
                                                const char *symbols) {
  string_t *res = create_clear_string();
  char symbol = 0;
  while ((symbol = fgetc(file)) != EOF) {
    if (strchr(symbols, symbol) != NULL)
      continue;
    add_char(res, symbol);
  }
  return res;
}

string_t *remove_all_symbols(string_t *string, const char *symbols) {
  string_t *res = create_clear_string();
  for (size_t i = 0; i < string->size; i++) {
    if (strchr(symbols, res->string[i]) != NULL)
      continue;
    add_char(res, res->string[i]);
  }
  return res;
}

int is_equal(string_t *str1, string_t *str2) {
  return strcmp(str1->string, str2->string) == 0;
}

void concat(string_t *restrict base, const string_t *restrict addiction) {
  base->string =
      (char *)realloc(base->string, base->size + addiction->size - 1);
  base->string = strcat(base->string, addiction->string);
}

string_t *replace(const string_t *source, const string_t *replacement,
                  const string_t *stamping) {
  string_t *result = create_clear_string();
  const char *tmp = source->string, *index = NULL;

  while ((index = strstr(tmp, replacement->string)) != NULL) {
    for (long int i = 0; i < tmp - index + 1; i++) {
      add_char(result, tmp[i]);
    }
    concat(result, stamping);
    tmp = index + replacement->size;
  }
  return result;
}

int is_digit(char symbol) { return symbol >= '0' && symbol <= '9'; }

void shift_string(string_t *string, size_t shift) {
  char *new_string = (char *)malloc(sizeof(char) * (string->size - shift));
  memcpy(new_string, string->string + shift, string->size - shift);
  free(string->string);
  string->string = new_string;
  string->size -= shift;
}

void concat_n(string_t *res, const string_t *src, size_t n) {
  strncat(res->string, src->string, n);
}

int compare_string(string_t *str1, string_t *str2) {
  return strcmp(str1->string, str2->string);
}

void copy_string(const string_t *src, string_t *dest) {
  dest->size = src->size;
  dest->string = (char *)malloc(sizeof(char) * src->size);
  memcpy(dest->string, src->string, src->size);
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

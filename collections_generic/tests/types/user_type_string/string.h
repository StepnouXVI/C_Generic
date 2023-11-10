#ifndef STRING_FOR_TESTS
#define STRING_FOR_TESTS

#include <stddef.h>
typedef struct string_t {
  char *string;
  size_t size;
} string_t;

string_t *create_string(const char *string);
void destroy_string(string_t *string);
void copy_string(const string_t *src, string_t *dest);
int compare_strings(const string_t *a, const string_t *b);

void destruct_string_array(string_t *array, size_t size);
string_t *make_random_string_array(size_t size);
size_t get_hash_code_string(size_t capacity, size_t key_gen,
                            const string_t *key);
#endif
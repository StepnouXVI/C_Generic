#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>
#include <stdio.h>

/**
 * @brief Structure representing a string.
 *
 * @param string Pointer to the character array.
 * @param size Size of the character array.
 */
typedef struct string_t {
  char *string; ///< Pointer to the character array.
  size_t size;  ///< Size of the character array.
} string_t;

/**
 * @brief Deallocates memory for a string.
 *
 * @param string Pointer to the string to be deallocated.
 * @warning Ensure that the memory allocated for the string was obtained using malloc or realloc.
 */
void destruct_string(string_t *string);

/**
 * @brief Creates a new empty string.
 *
 * @return Pointer to the created string.
 * @warning Ensure that the memory allocated for the string is released using destruct_string.
 */
string_t *create_clear_string(void);

/**
 * @brief Adds a character to the string.
 *
 * @param string Pointer to the string.
 * @param symbol The character to be added.
 * @warning Ensure that the memory allocated for the string was obtained using malloc or realloc.
 */
void add_char(string_t *string, char symbol);

/**
 * @brief Reads a string from a file, excluding specified symbols.
 *
 * @param file Pointer to the file from which to read the string.
 * @param symbols The symbols to be excluded from the string.
 * @return Pointer to the created string.
 * @warning Ensure that the memory allocated for the string is released using destruct_string.
 */
string_t *read_string_without_specified_symbols(FILE *file, const char *symbols);

/**
 * @brief Removes specified symbols from the string.
 *
 * @param string Pointer to the string.
 * @param symbols The symbols to be removed.
 * @return Pointer to the modified string.
 * @warning Ensure that the memory allocated for the string was obtained using malloc or realloc.
 */
string_t *remove_all_symbols(string_t *string, const char *symbols);

/**
 * @brief Checks if two strings are equal.
 *
 * @param str1 Pointer to the first string.
 * @param str2 Pointer to the second string.
 * @return 1 if the strings are equal, 0 otherwise.
 * @warning Ensure that the memory allocated for the strings was obtained using malloc or realloc.
 */
int is_equal(string_t *str1, string_t *str2);

/**
 * @brief Concatenates two strings.
 *
 * @param base Pointer to the base string.
 * @param addiction Pointer to the string to be concatenated.
 * @warning Ensure that the memory allocated for the strings was obtained using malloc or realloc.
 */
void concat(string_t * __restrict__ base, const string_t *__restrict__ addiction);

/**
 * @brief Replaces occurrences of a specified string with another string.
 *
 * @param source Pointer to the source string.
 * @param replacement Pointer to the string to replace.
 * @param stamping Pointer to the string to be inserted.
 * @return Pointer to the modified string.
 * @warning Ensure that the memory allocated for the strings is released using destruct_string.
 */
string_t *replace(const string_t *source, const string_t *replacement, const string_t *stamping);

/**
 * @brief Checks if a character is a digit.
 *
 * @param symbol The character to be checked.
 * @return 1 if the character is a digit, 0 otherwise.
 */
int is_digit(char symbol);

/**
 * @brief Shifts the string by a specified number of characters.
 *
 * @param string Pointer to the string to be shifted.
 * @param shift The number of characters to shift.
 * @warning Ensure that the memory allocated for the string was obtained using malloc or realloc.
 */
void shift_string(string_t *string, size_t shift);

/**
 * @brief Concatenates a specified number of characters from the source string to the destination string.
 *
 * @param res Pointer to the destination string.
 * @param src Pointer to the source string.
 * @param n The number of characters to concatenate.
 * @warning Ensure that the memory allocated for the strings was obtained using malloc or realloc.
 */
void concat_n(string_t *res, const string_t *src, size_t n);

/**
 * @brief Compares two strings.
 *
 * @param str1 Pointer to the first string.
 * @param str2 Pointer to the second string.
 * @return A negative value if str1 is less than str2, 0 if they are equal, a positive value if str1 is greater than str2.
 * @warning Ensure that the memory allocated for the strings was obtained using malloc or realloc.
 */
int compare_string(string_t *str1, string_t *str2);

/**
 * @brief Copies the contents of one string to another.
 *
 * @param src Pointer to the source string.
 * @param dest Pointer to the destination string.
 * @warning Ensure that the memory allocated for the strings was obtained using malloc or realloc.
 */
void copy_string(const string_t *src, string_t *dest);

/**
 * @brief Calculates the hash code for a string.
 *
 * @param capacity The capacity of the hash table.
 * @param key_gen The key generation factor.
 * @param key Pointer to the string key.
 * @return The calculated hash code.
 */
size_t get_hash_code_string(size_t capacity, size_t key_gen, const string_t* key);

/**
 * @brief Creates a new string from a source character array.
 *
 * @param src Pointer to the source character array.
 * @return Pointer to the created string.
 * @warning Ensure that the memory allocated for the string is released using destruct_string.
 */
string_t* create_string(const char* src);


#endif
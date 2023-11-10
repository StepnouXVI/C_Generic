#ifndef KEY_VALUE_PAIR_H
#define KEY_VALUE_PAIR_H

/**
 * @brief Structure representing a key-value pair.
 *
 * @details The `key_value_pair` structure represents a key-value pair, where
 * `key` and `value` are pointers to arbitrary data.
 *
 * @param key Pointer to the key data.
 * @param value Pointer to the value data.
 */
typedef struct key_value_pair_t {
  void *key;   /**< Pointer to the key data. */
  void *value; /**< Pointer to the value data. */
} key_value_pair_t;

#endif
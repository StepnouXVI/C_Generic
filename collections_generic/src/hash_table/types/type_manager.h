#ifndef TYPE_MANAGER_H
#define TYPE_MANAGER_H
#include "../../types/functions.h"


/**
 * @brief A struct to manage object types.
 *
 * This struct is used to manage object types in universal collections.
 * It contains function pointers to compare, copy, and destruct objects.
 *
 * @param compare Function pointer to compare objects.
 * @param copy Function pointer to copy objects.
 * @param destruct Function pointer to destruct objects.
 * @param size_of_obj Size of an object.
 */
typedef struct type_manager_t {
  size_t size_of_obj; /**< Size of an object. */
  compare_t compare; /**< Function pointer to compare objects. */
  copy_t copy;       /**< Function pointer to copy objects. */
  destruct_t destruct; /**< Function pointer to destruct objects. */
} type_manager_t;


#endif
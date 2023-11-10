#ifndef HASH_TABLE_TESTS_H
#define HASH_TABLE_TESTS_H

#include "../../src/hash_table/hash_table.h"
#include <check.h>
Suite *create_test_suite_hash_table_str_key_int_value(void);
Suite *create_test_suite_hash_table_int_key_float_value(void);

#endif
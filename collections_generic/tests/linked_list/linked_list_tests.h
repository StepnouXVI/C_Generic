#ifndef LINKED_LIST_TESTS_H
#define LINKED_LIST_TESTS_H

#include "../../src/linked_list/linked_list.h"
#include <check.h>
Suite *create_test_suite_linked_list_struct_t(void);
Suite *create_test_suite_linked_list_int(void);
Suite *create_test_suite_linked_list_string_t(void);
#endif
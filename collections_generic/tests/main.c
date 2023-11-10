#include "linked_list/linked_list_tests.h"
#include "hash_table/hash_table_tests.h"
#include <check.h>

#include <check.h>

int main(void) {

  SRunner *runner = srunner_create(create_test_suite_linked_list_int());

  srunner_add_suite(runner, create_test_suite_linked_list_struct_t());
  srunner_add_suite(runner, create_test_suite_linked_list_string_t());
  srunner_add_suite(runner, create_test_suite_hash_table_int_key_float_value());
  srunner_add_suite(runner, create_test_suite_hash_table_str_key_int_value());




  srunner_set_log(runner, "test.log");

  srunner_run_all(runner, CK_MINIMAL);

  int num_failed = srunner_ntests_failed(runner);

  srunner_free(runner);

  return (num_failed == 0) ? 0 : 1;
}

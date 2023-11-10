#include "../types/user_type/user_type.h"
#include "../types/user_type_string/string.h"
#include "linked_list_tests.h"

#include <check.h>

#define ck_assert_struct_eq(n1, n2)                                            \
  ck_assert_int_eq((n1).c, (n2).c);                                            \
  ck_assert_int_eq((n1).a, (n2).a);                                            \
  ck_assert_int_eq((n1).b, (n2).b);

START_TEST(push_front_pop_back_int) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
  struct_t *array = make_random_struct_array(10);

  for (int i = 0; i < 10; i++) {
    push_front(list, &array[i]);
  }

  for (int i = 0; i < 10; i++) {
    struct_t tmp = {0};
    pop_back(list, &tmp);
    ck_assert_struct_eq(tmp, array[i]);
  }

  free(array);
  destruct_linked_list(list);
}
END_TEST

START_TEST(push_front_pop_front_int) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
  struct_t *array = make_random_struct_array(10);

  for (int i = 0; i < 10; i++) {
    push_front(list, &array[i]);
  }

  for (int i = 9; i >= 0; i--) {
    struct_t tmp = {0};
    pop_front(list, &tmp);
    ck_assert_struct_eq(tmp, array[i]);
  }

  free(array);
  destruct_linked_list(list);
}
END_TEST

START_TEST(push_back_pop_front_int) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
  struct_t *array = make_random_struct_array(10);

  for (int i = 0; i < 10; i++) {
    push_back(list, &array[i]);
  }

  for (int i = 0; i < 10; i++) {
    struct_t tmp = {0};
    pop_front(list, &tmp);
    ck_assert_struct_eq(tmp, array[i]);
  }

  free(array);
  destruct_linked_list(list);
}
END_TEST

START_TEST(push_back_pop_back_int) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
  struct_t *array = make_random_struct_array(10);

  for (int i = 0; i < 10; i++) {
    push_back(list, &array[i]);
  }

  for (int i = 9; i >= 0; i--) {
    struct_t tmp = {0};
    pop_back(list, &tmp);
    ck_assert_struct_eq(tmp, array[i]);
  }

  free(array);
  destruct_linked_list(list);
}
END_TEST

START_TEST(get_by_index_int_normal_push_back) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
  struct_t array[3] = {{0, 0, 1}, {0, 0, 2}, {0, 0, 3}};

  for (int i = 0; i < 3; i++) {
    push_back(list, &array[i]);
  }

  struct_t res = *(struct_t *)(get_by_index_from_linked_list(list, 2));
  ck_assert_struct_eq(res, array[2]);
  destruct_linked_list(list);
}
END_TEST

START_TEST(get_by_index_int_normal_push_front) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
    struct_t array[3] = {{0, 0, 1}, {0, 0, 2}, {0, 0, 3}};

  for (int i = 0; i < 3; i++) {
    push_front(list, &array[i]);
  }

  struct_t res = *(struct_t *)(get_by_index_from_linked_list(list, 0));
  ck_assert_struct_eq(res, array[2]);
  destruct_linked_list(list);
}
END_TEST

START_TEST(get_by_index_int_incorrect_index) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
    struct_t array[3] = {{0, 0, 1}, {0, 0, 2}, {0, 0, 3}};

  for (int i = 0; i < 3; i++) {
    push_back(list, &array[i]);
  }

  void *res = (get_by_index_from_linked_list(list, 3));
  ck_assert_ptr_null(res);
  destruct_linked_list(list);
}
END_TEST

START_TEST(get_by_index_with_copy_int_normal_push_back) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
    struct_t array[3] = {{0, 0, 1}, {0, 0, 2}, {0, 0, 3}};

  for (int i = 0; i < 3; i++) {
    push_back(list, &array[i]);
  }
  struct_t res = {0};
  bool_t status = get_by_index_with_copy_from_linked_list(list, 2, &res);
  ck_assert_int_eq(status, true);
  ck_assert_struct_eq(res, array[2]);
  destruct_linked_list(list);
}
END_TEST

START_TEST(get_by_index_with_copy_int_normal_push_front) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
    struct_t array[3] = {{0, 0, 1}, {0, 0, 2}, {0, 0, 3}};

  for (int i = 0; i < 3; i++) {
    push_front(list, &array[i]);
  }

  struct_t res = {0};
  bool_t status = get_by_index_with_copy_from_linked_list(list, 2, &res);
  ck_assert_int_eq(status, true);
  ck_assert_struct_eq(res, array[0]);
  destruct_linked_list(list);
}
END_TEST

START_TEST(get_by_index_with_copy_int_incorrect_index_with_copy) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
    struct_t array[3] = {{0, 0, 1}, {0, 0, 2}, {0, 0, 3}};

  for (int i = 0; i < 3; i++) {
    push_back(list, &array[i]);
  }

  struct_t res = {0};
  bool_t status = get_by_index_with_copy_from_linked_list(list, 3, &res);
  ck_assert_int_eq(status, false);
  destruct_linked_list(list);
}
END_TEST

START_TEST(is_empty_int_and_push_pop_peek) {
  linked_list_t *list = init_linked_list(struct_t, NULL, NULL, NULL);
  struct_t A = {0};
  ck_assert_int_eq(is_empty_list(list), true);
  push_back(list, &A);
  ck_assert_int_eq(is_empty_list(list), false);
  peek_back(list, &A);
  ck_assert_int_eq(is_empty_list(list), false);
  peek_front(list, &A);
  ck_assert_int_eq(is_empty_list(list), false);
  pop_front(list, &A);
  ck_assert_int_eq(is_empty_list(list), true);
  push_front(list, &A);
  ck_assert_int_eq(is_empty_list(list), false);
  pop_back(list, &A);
  ck_assert_int_eq(is_empty_list(list), true);
  destruct_linked_list(list);
}

//====================================================================================//
//=============================[ADVANCED_FUNCTIONS]===================================//
//====================================================================================//

START_TEST(test_contains_in_linked_list_empty_list) {
  linked_list_t *empty_list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element = {.a = 0, .b = 0, .c = 10};
  bool_t is_element_found = contains_in_linked_list(empty_list, &element);
  ck_assert(is_element_found == false);
  destruct_linked_list(empty_list);
}
END_TEST

START_TEST(test_contains_in_linked_list_element_found) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  push_back(list, &element2);
  bool_t is_element_found = contains_in_linked_list(list, &element1);
  ck_assert(is_element_found == true);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_contains_in_linked_list_element_not_found) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  bool_t is_element_found = contains_in_linked_list(list, &element2);
  ck_assert(is_element_found == false);
  destruct_linked_list(list);
}
END_TEST

START_TEST(count_in_linked_list_empty_list) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t search_element = {.a = 0, .b = 0, .c = 10};
  size_t count = count_in_linked_list(list, &search_element);
  ck_assert_int_eq(count, 0);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_element_not_present) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);

  struct_t search_element = {.a = 0, .b = 0, .c = 10};
  struct_t element1 = {.a = 0, .b = 0, .c = 20};
  struct_t element2 = {.a = 0, .b = 0, .c = 30};
  struct_t element3 = {.a = 0, .b = 0, .c = 40};
  push_front(list, &element1);
  push_front(list, &element2);
  push_front(list, &element3);
  size_t count = count_in_linked_list(list, &search_element);
  ck_assert_int_eq(count, 0);
  destruct_linked_list(list);
}
END_TEST

START_TEST(count_in_linked_list_element_at_beginning) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);

  struct_t search_element = {.a = 0, .b = 0, .c = 10};
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  struct_t element3 = {.a = 0, .b = 0, .c = 30};
  push_front(list, &element1);
  push_front(list, &element2);
  push_front(list, &element3);
  size_t count = count_in_linked_list(list, &search_element);
  ck_assert_int_eq(count, 1);
  destruct_linked_list(list);
}
END_TEST

START_TEST(count_in_linked_list_element_at_end) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);

  struct_t search_element = {.a = 0, .b = 0, .c = 10};
  struct_t element1 = {.a = 0, .b = 0, .c = 20};
  struct_t element2 = {.a = 0, .b = 0, .c = 30};
  struct_t element3 = {.a = 0, .b = 0, .c = 10};
  push_front(list, &element1);
  push_front(list, &element2);
  push_front(list, &element3);
  size_t count = count_in_linked_list(list, &search_element);
  ck_assert_int_eq(count, 1);
  destruct_linked_list(list);
}
END_TEST

START_TEST(count_in_linked_list_element_in_middle) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);

  struct_t search_element = {.a = 0, .b = 0, .c = 10};
  struct_t element1 = {.a = 0, .b = 0, .c = 20};
  struct_t element2 = {.a = 0, .b = 0, .c = 10};
  struct_t element3 = {.a = 0, .b = 0, .c = 30};
  push_front(list, &element1);
  push_front(list, &element2);
  push_front(list, &element3);
  size_t count = count_in_linked_list(list, &search_element);
  ck_assert_int_eq(count, 1);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_remove_from_linked_list_empty_list) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t data = {.a = 0, .b = 0, .c = 42};
  bool_t success = remove_from_linked_list(list, &data);
  ck_assert_int_eq(success, false);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_remove_from_linked_list_element_not_found) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  bool_t success = remove_from_linked_list(list, &element2);
  ck_assert_int_eq(success, false);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_remove_from_linked_list_element_found) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  push_back(list, &element2);
  bool_t success = remove_from_linked_list(list, &element1);
  ck_assert_int_eq(success, true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_remove_all_from_linked_list_empty_list) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t data = {.a = 0, .b = 0, .c = 42};
  bool_t success = remove_all_from_linked_list(list, &data);
  ck_assert_int_eq(success, false);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_remove_all_from_linked_list_element_not_found) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  bool_t success = remove_all_from_linked_list(list, &element2);
  ck_assert_int_eq(success, false);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_remove_all_from_linked_list_element_found_once) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  push_back(list, &element2);
  bool_t success = remove_all_from_linked_list(list, &element1);
  ck_assert_int_eq(success, true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
}

START_TEST(test_remove_all_from_linked_list_element_found_multiple_times) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  push_back(list, &element2);
  push_back(list, &element1);
  bool_t success = remove_all_from_linked_list(list, &element1);
  ck_assert_int_eq(success, true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_find_in_linked_list_empty_list) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t data = {.a = 0, .b = 0, .c = 42};
  long long int index = find_in_linked_list(list, &data);
  ck_assert_int_eq(index, -1);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_find_in_linked_list_element_not_found) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  long long int index = find_in_linked_list(list, &element2);
  ck_assert_int_eq(index, -1);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_find_in_linked_list_element_found) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  push_back(list, &element2);
  long long int index = find_in_linked_list(list, &element1);
  ck_assert_int_eq(index, 0);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_r_find_in_linked_list_empty_list) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t data = {.a = 0, .b = 0, .c = 42};
  long long int index = r_find_in_linked_list(list, &data);
  ck_assert_int_eq(index, -1);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_r_find_in_linked_list_element_not_found) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  long long int index = r_find_in_linked_list(list, &element2);
  ck_assert_int_eq(index, -1);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_r_find_in_linked_list_element_found) {
  linked_list_t *list =
      init_linked_list(struct_t, (compare_t)compare_structs, NULL, NULL);
  struct_t element1 = {.a = 0, .b = 0, .c = 10};
  struct_t element2 = {.a = 0, .b = 0, .c = 20};
  push_back(list, &element1);
  push_back(list, &element2);
  push_back(list, &element1);
  long long int index = r_find_in_linked_list(list, &element1);
  ck_assert_int_eq(index, 2);
  destruct_linked_list(list);
}
END_TEST

void add_push_pop_tests_struct_t(Suite *suite) {
  TCase *tcase_push_pop = tcase_create("Push pop");
  tcase_add_test(tcase_push_pop, push_back_pop_back_int);
  tcase_add_test(tcase_push_pop, push_front_pop_back_int);
  tcase_add_test(tcase_push_pop, push_back_pop_front_int);
  tcase_add_test(tcase_push_pop, push_front_pop_front_int);
  suite_add_tcase(suite, tcase_push_pop);
}

void add_get_value_by_index_tests_struct_t(Suite *suite) {
  TCase *tcase_get_value_by_index = tcase_create("Get value from linked list");
  tcase_add_test(tcase_get_value_by_index, get_by_index_int_incorrect_index);
  tcase_add_test(tcase_get_value_by_index, get_by_index_int_normal_push_back);
  tcase_add_test(tcase_get_value_by_index, get_by_index_int_normal_push_front);
  suite_add_tcase(suite, tcase_get_value_by_index);
}

void add_get_value_by_index_with_copy_tests_struct_t(Suite *suite) {
  TCase *tcase_get_value_by_index_with_copy =
      tcase_create("Get value from linked list with copy");
  tcase_add_test(tcase_get_value_by_index_with_copy,
                 get_by_index_with_copy_int_normal_push_back);
  tcase_add_test(tcase_get_value_by_index_with_copy,
                 get_by_index_with_copy_int_normal_push_front);
  tcase_add_test(tcase_get_value_by_index_with_copy,
                 get_by_index_with_copy_int_incorrect_index_with_copy);
  suite_add_tcase(suite, tcase_get_value_by_index_with_copy);
}

void add_is_empty_tests_struct_t(Suite *suite) {
  TCase *tcase_is_empty = tcase_create("Is empty linked list");
  tcase_add_test(tcase_is_empty, is_empty_int_and_push_pop_peek);
  suite_add_tcase(suite, tcase_is_empty);
}

void add_contains_tests_struct_t(Suite *suite) {
  TCase *tcase_contains = tcase_create("Contains in linked list");
  tcase_add_test(tcase_contains, test_contains_in_linked_list_element_found);
  tcase_add_test(tcase_contains,
                 test_contains_in_linked_list_element_not_found);
  tcase_add_test(tcase_contains, test_contains_in_linked_list_empty_list);
  suite_add_tcase(suite, tcase_contains);
}

void add_count_tests_struct_t(Suite *suite) {
  TCase *tcase_count = tcase_create("Count in linked list");
  tcase_add_test(tcase_count, count_in_linked_list_element_at_beginning);
  tcase_add_test(tcase_count, count_in_linked_list_element_at_end);
  tcase_add_test(tcase_count, count_in_linked_list_empty_list);
  tcase_add_test(tcase_count, count_in_linked_list_element_in_middle);
  tcase_add_test(tcase_count, test_element_not_present);
  suite_add_tcase(suite, tcase_count);
}

void add_remove_tests_struct_t(Suite *suite) {
  TCase *tcase_remove_from_linked_list =
      tcase_create("Remove from linked list");
  tcase_add_test(tcase_remove_from_linked_list,
                 test_remove_from_linked_list_empty_list);
  tcase_add_test(tcase_remove_from_linked_list,
                 test_remove_from_linked_list_element_not_found);
  tcase_add_test(tcase_remove_from_linked_list,
                 test_remove_from_linked_list_element_found);
  suite_add_tcase(suite, tcase_remove_from_linked_list);
}

void add_find_tests_struct_t(Suite *suite) {
  TCase *tcase_find_in_linked_list = tcase_create("Find in linked list");
  tcase_add_test(tcase_find_in_linked_list,
                 test_find_in_linked_list_empty_list);
  tcase_add_test(tcase_find_in_linked_list,
                 test_find_in_linked_list_element_not_found);
  tcase_add_test(tcase_find_in_linked_list,
                 test_find_in_linked_list_element_found);
  suite_add_tcase(suite, tcase_find_in_linked_list);
}

void add_r_find_tests_struct_t(Suite *suite) {
  TCase *r_find_in_linked_list = tcase_create("R find in linked list");
  tcase_add_test(r_find_in_linked_list, test_r_find_in_linked_list_empty_list);
  tcase_add_test(r_find_in_linked_list,
                 test_r_find_in_linked_list_element_not_found);
  tcase_add_test(r_find_in_linked_list,
                 test_r_find_in_linked_list_element_found);
  suite_add_tcase(suite, r_find_in_linked_list);
}

void add_remove_all_from_linked_list_tests_struct_t(Suite *suite) {
  TCase *tcase_remove_all_from_linked_list =
      tcase_create("Remove all from linked list");
  tcase_add_test(tcase_remove_all_from_linked_list,
                 test_remove_all_from_linked_list_empty_list);
  tcase_add_test(tcase_remove_all_from_linked_list,
                 test_remove_all_from_linked_list_element_not_found);
  tcase_add_test(tcase_remove_all_from_linked_list,
                 test_remove_all_from_linked_list_element_found_once);
  tcase_add_test(tcase_remove_all_from_linked_list,
                 test_remove_all_from_linked_list_element_found_multiple_times);
  suite_add_tcase(suite, tcase_remove_all_from_linked_list);
}

Suite *create_test_suite_linked_list_struct_t(void) {
  Suite *suite = suite_create("Linked list struct  tests_struct_t");
  add_push_pop_tests_struct_t(suite);
  add_get_value_by_index_tests_struct_t(suite);
  add_get_value_by_index_with_copy_tests_struct_t(suite);
  add_is_empty_tests_struct_t(suite);
  add_contains_tests_struct_t(suite);
  add_count_tests_struct_t(suite);
  add_remove_tests_struct_t(suite);
  add_find_tests_struct_t(suite);
  add_r_find_tests_struct_t(suite);
  add_remove_all_from_linked_list_tests_struct_t(suite);

  return suite;
}

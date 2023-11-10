#include "../types/int/int.h"
#include "../types/user_type/user_type.h"
#include "../types/user_type_string/string.h"
#include "linked_list_tests.h"

#include <check.h>

START_TEST(test_peek_front_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  string_t *str2 = create_string("world");
  push_back(list, str1);
  push_back(list, str2);
  string_t peeked_str;
  ck_assert(peek_front(list, &peeked_str));
  ck_assert_str_eq(peeked_str.string, "hello");
  destruct_linked_list(list);
  destroy_string(str1);
  destroy_string(str2);
  free(peeked_str.string);
}
END_TEST

START_TEST(test_peek_front_empty_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t peeked_str;

  ck_assert(!peek_front(list, &peeked_str));
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_peek_back_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  string_t *str2 = create_string("world");
  push_back(list, str1);
  push_back(list, str2);
  string_t peeked_str = {0};
  ck_assert(peek_back(list, &peeked_str));
  ck_assert_str_eq(peeked_str.string, "world");
  destruct_linked_list(list);
  destroy_string(str1);
  free(peeked_str.string);
  destroy_string(str2);
}
END_TEST

START_TEST(test_peek_back_empty_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t peeked_str = {0};
  ck_assert(!peek_back(list, &peeked_str));
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_push_back_no_null) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  push_back(list, str1);
  push_back(list, NULL);
  ck_assert_int_eq(list->size, 1);
  ck_assert_str_eq(((string_t *)(list->tail->data))->string, "hello");
  destruct_linked_list(list);
  destroy_string(str1);
}
END_TEST

START_TEST(test_push_back_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  string_t *str2 = create_string("world");
  push_back(list, str1);
  push_back(list, str2);
  ck_assert_int_eq(list->size, 2);
  ck_assert_str_eq(((string_t *)(list->tail->data))->string, "world");
  destruct_linked_list(list);
  destroy_string(str1);
  destroy_string(str2);
}
END_TEST

START_TEST(test_push_front_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  string_t *str2 = create_string("world");
  push_front(list, str1);
  push_front(list, str2);
  ck_assert_int_eq(list->size, 2);
  ck_assert_str_eq(((string_t *)(list->tail->data))->string, "hello");
  destruct_linked_list(list);
  destroy_string(str1);
  destroy_string(str2);
}
END_TEST

START_TEST(test_push_front_empty_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  push_front(list, NULL);
  ck_assert_int_eq(list->size, 0);
  ck_assert_ptr_eq(list->head, NULL);
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_pop_back_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  string_t *str2 = create_string("world");
  push_back(list, str1);
  push_back(list, str2);
  string_t popped_str = {0};
  ck_assert(pop_back(list, &popped_str));
  ck_assert_int_eq(list->size, 1);
  ck_assert_str_eq(popped_str.string, "world");
  destruct_linked_list(list);
  destroy_string(str1);
  destroy_string(str2);
  free(popped_str.string);
}
END_TEST

START_TEST(test_pop_back_empty_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t popped_str = {0};
  ck_assert(!pop_back(list, &popped_str));
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_pop_front_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  string_t *str2 = create_string("world");
  push_front(list, str1);
  push_front(list, str2);
  string_t popped_str = {0};
  ck_assert(pop_front(list, &popped_str));
  ck_assert_int_eq(list->size, 1);
  ck_assert_str_eq(popped_str.string, "world");
  destruct_linked_list(list);
  destroy_string(str1);
  destroy_string(str2);
  free(popped_str.string);
}
END_TEST

START_TEST(test_pop_front_empty_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t popped_str = {0};
  ck_assert(!pop_front(list, &popped_str));
  destruct_linked_list(list);
}
END_TEST

START_TEST(test_get_by_index_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  string_t *str2 = create_string("world");
  string_t *str3 = create_string("my");
  string_t *str4 = create_string("name");
  string_t *str5 = create_string("is");
  string_t *str6 = create_string("AI");
  push_back(list, str1);
  push_back(list, str2);
  push_back(list, str3);
  push_back(list, str4);
  push_back(list, str5);
  push_back(list, str6);
  string_t *str_ptr1 = (string_t *)get_by_index_from_linked_list(list, 2);
  string_t *str_ptr2 = (string_t *)get_by_index_from_linked_list(list, 5);
  ck_assert_str_eq(str_ptr1->string, "my");
  ck_assert_str_eq(str_ptr2->string, "AI");
  destroy_string(str1);
  destroy_string(str2);
  destroy_string(str3);
  destroy_string(str4);
  destroy_string(str5);
  destroy_string(str6);
  destruct_linked_list(list);
}

START_TEST(test_get_by_index_empty_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  ck_assert_ptr_eq(get_by_index_from_linked_list(list, 0), NULL);
  destruct_linked_list(list);
}

START_TEST(test_get_by_index_out_of_bounds_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  string_t *str2 = create_string("world");
  push_back(list, str1);
  push_back(list, str2);
  ck_assert_ptr_eq(get_by_index_from_linked_list(list, 2), NULL);
  destroy_string(str1);
  destroy_string(str2);
  destruct_linked_list(list);
}

START_TEST(test_get_by_index_with_copy_from_linked_list_valid_index) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  string_t *str2 = create_string("world");
  string_t *str3 = create_string("my");
  string_t *str4 = create_string("name");
  string_t *str5 = create_string("is");
  string_t *str6 = create_string("AI");
  push_back(list, str1);
  push_back(list, str2);
  push_back(list, str3);
  push_back(list, str4);
  push_back(list, str5);
  push_back(list, str6);
  string_t buffer = {0};
  ck_assert(get_by_index_with_copy_from_linked_list(list, 1, &buffer));
  ck_assert_str_eq(buffer.string, "world");
  destroy_string(str1);
  destroy_string(str2);
  destroy_string(str3);
  destroy_string(str4);
  destroy_string(str5);
  destroy_string(str6);
  destruct_linked_list(list);
  free(buffer.string);
}

START_TEST(test_get_by_index_with_copy_from_linked_list_invalid_index) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *str1 = create_string("hello");
  string_t *str2 = create_string("world");
  string_t *str3 = create_string("my");
  push_back(list, str1);
  push_back(list, str2);
  push_back(list, str3);
  string_t buffer = {0};
  ck_assert(!get_by_index_with_copy_from_linked_list(list, 5, &buffer));
  destroy_string(str1);
  destroy_string(str2);
  destroy_string(str3);
  destruct_linked_list(list);
}

START_TEST(test_get_by_index_with_copy_from_linked_list_empty_list) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t buffer = {0};
  ck_assert(!get_by_index_with_copy_from_linked_list(list, 0, &buffer));
  destruct_linked_list(list);
}

START_TEST(test_get_size_of_linked_list_string_t) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *array = make_random_string_array(5);

  for (int i = 0; i < 5; i++) {
    push_back(list, &array[i]);
  }

  ck_assert_int_eq(get_size_of_linked_list(list), 5);

  destruct_string_array(array, 5);
  destruct_linked_list(list);
}
END_TEST
START_TEST(test_contains_in_linked_list_string_t_element_found) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  bool_t is_element_found = contains_in_linked_list(list, element1);
  ck_assert(is_element_found == true);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_contains_in_linked_list_string_t_element_not_found) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  bool_t is_element_found = contains_in_linked_list(list, element2);
  ck_assert(is_element_found == false);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_contains_in_linked_list_string_t_empty_list) {
  linked_list_t *empty_list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element = create_string("hello");
  bool_t is_element_found = contains_in_linked_list(empty_list, element);
  ck_assert(is_element_found == false);
  destruct_linked_list(empty_list);
  destroy_string(element);
}
END_TEST

START_TEST(test_count_in_linked_list_empty_list) {
  linked_list_t *empty_list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element = create_string("hello");
  size_t count = count_in_linked_list(empty_list, element);
  ck_assert_int_eq(count, 0);
  destruct_linked_list(empty_list);
  destroy_string(element);
}
END_TEST

START_TEST(test_count_in_linked_list_element_found_once) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  size_t count = count_in_linked_list(list, element1);
  ck_assert_int_eq(count, 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}

START_TEST(test_count_in_linked_list_element_found_multiple_times) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  push_back(list, element1);
  push_back(list, element1);
  push_back(list, element1);
  size_t count = count_in_linked_list(list, element1);
  ck_assert_int_eq(count, 3);
  destruct_linked_list(list);
  destroy_string(element1);
}

START_TEST(test_count_in_linked_list_element_not_found) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  size_t count = count_in_linked_list(list, element2);
  ck_assert_int_eq(count, 0);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_by_index_from_linked_list_empty_list) {
  linked_list_t *empty_list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  bool_t is_node_removed = remove_by_index_from_linked_list(empty_list, 0);
  ck_assert(is_node_removed == false);
  ck_assert_int_eq(get_size_of_linked_list(empty_list), 0);
  destruct_linked_list(empty_list);
}
END_TEST

START_TEST(test_remove_by_index_from_linked_list_invalid_index) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  push_back(list, element1);
  bool_t is_node_removed = remove_by_index_from_linked_list(list, 1);
  ck_assert(is_node_removed == false);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
}
END_TEST

START_TEST(test_remove_by_index_from_linked_list_valid_index) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  bool_t is_node_removed = remove_by_index_from_linked_list(list, 1);
  ck_assert(is_node_removed == true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_by_index_from_linked_list_first_index) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  bool_t is_node_removed = remove_by_index_from_linked_list(list, 0);
  ck_assert(is_node_removed == true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_by_index_from_linked_list_last_index) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  bool_t is_node_removed = remove_by_index_from_linked_list(list, 1);
  ck_assert(is_node_removed == true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_from_linked_list_empty_list) {
  linked_list_t *empty_list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element_to_remove = create_string("hello");
  bool_t is_node_removed =
      remove_from_linked_list(empty_list, element_to_remove);
  ck_assert(is_node_removed == false);
  ck_assert_int_eq(get_size_of_linked_list(empty_list), 0);
  destruct_linked_list(empty_list);
  destroy_string(element_to_remove);
}
END_TEST

START_TEST(test_remove_from_linked_list_invalid_data) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  bool_t is_node_removed = remove_from_linked_list(list, element2);
  ck_assert(is_node_removed == false);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_from_linked_list_valid_data) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  bool_t is_node_removed = remove_from_linked_list(list, element2);
  ck_assert(is_node_removed == true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_from_linked_list_first_occurrence) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  bool_t is_node_removed = remove_from_linked_list(list, element1);
  ck_assert(is_node_removed == true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_from_linked_list_last_occurrence) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  bool_t is_node_removed = remove_from_linked_list(list, element2);
  ck_assert(is_node_removed == true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_all_from_linked_list_empty_list) {
  linked_list_t *empty_list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element_to_remove = create_string("hello");
  bool_t is_node_removed =
      remove_all_from_linked_list(empty_list, element_to_remove);
  ck_assert(is_node_removed == false);
  ck_assert_int_eq(get_size_of_linked_list(empty_list), 0);
  destruct_linked_list(empty_list);
  destroy_string(element_to_remove);
}
END_TEST

START_TEST(test_remove_all_from_linked_list_invalid_data) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  bool_t is_node_removed = remove_all_from_linked_list(list, element2);
  ck_assert(is_node_removed == false);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_all_from_linked_list_valid_data) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  bool_t is_node_removed = remove_all_from_linked_list(list, element2);
  ck_assert(is_node_removed == true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_all_from_linked_list_first_occurrence) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  bool_t is_node_removed = remove_all_from_linked_list(list, element1);
  ck_assert(is_node_removed == true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_remove_all_from_linked_list_last_occurrence) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  bool_t is_node_removed = remove_all_from_linked_list(list, element2);
  ck_assert(is_node_removed == true);
  ck_assert_int_eq(get_size_of_linked_list(list), 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_find_in_linked_list_empty_list) {
  linked_list_t *empty_list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element_to_find = create_string("hello");
  long long int index = find_in_linked_list(empty_list, element_to_find);
  ck_assert_int_eq(index, -1);
  destruct_linked_list(empty_list);
  destroy_string(element_to_find);
}
END_TEST

START_TEST(test_find_in_linked_list_invalid_data) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  long long int index = find_in_linked_list(list, element2);
  ck_assert_int_eq(index, -1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_find_in_linked_list_valid_data) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  long long int index = find_in_linked_list(list, element2);
  ck_assert_int_eq(index, 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_find_in_linked_list_first_occurrence) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  long long int index = find_in_linked_list(list, element1);
  ck_assert_int_eq(index, 0);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_find_in_linked_list_last_occurrence) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  push_back(list, element1);
  long long int index = find_in_linked_list(list, element1);
  ck_assert_int_eq(index, 0);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_r_find_in_linked_list_empty_list) {
  linked_list_t *empty_list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element_to_find = create_string("hello");
  long long int index = r_find_in_linked_list(empty_list, element_to_find);
  ck_assert_int_eq(index, -1);
  destruct_linked_list(empty_list);
  destroy_string(element_to_find);
}
END_TEST

START_TEST(test_r_find_in_linked_list_invalid_data) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  long long int index = r_find_in_linked_list(list, element2);
  ck_assert_int_eq(index, -1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_r_find_in_linked_list_valid_data) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  long long int index = r_find_in_linked_list(list, element2);
  ck_assert_int_eq(index, 1);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_r_find_in_linked_list_first_occurrence) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  long long int index = r_find_in_linked_list(list, element1);
  ck_assert_int_eq(index, 0);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

START_TEST(test_r_find_in_linked_list_last_occurrence) {
  linked_list_t *list =
      init_linked_list(string_t, (compare_t)compare_strings,
                       (destruct_t)destroy_string, (copy_t)copy_string);
  string_t *element1 = create_string("hello");
  string_t *element2 = create_string("world");
  push_back(list, element1);
  push_back(list, element2);
  push_back(list, element1);
  long long int index = r_find_in_linked_list(list, element1);
  ck_assert_int_eq(index, 2);
  destruct_linked_list(list);
  destroy_string(element1);
  destroy_string(element2);
}
END_TEST

void add_push_pop_tests_string_t(Suite *suite) {

  // Add the test cases to the suite
  TCase *tcase_push_pop = tcase_create("Push pop");
  tcase_add_test(tcase_push_pop, test_push_back_no_null);
  tcase_add_test(tcase_push_pop, test_push_front_string_t);
  tcase_add_test(tcase_push_pop, test_push_back_string_t);
  tcase_add_test(tcase_push_pop, test_push_front_empty_string_t);
  tcase_add_test(tcase_push_pop, test_pop_back_empty_string_t);
  tcase_add_test(tcase_push_pop, test_pop_front_string_t);
  tcase_add_test(tcase_push_pop, test_pop_back_string_t);
  tcase_add_test(tcase_push_pop, test_pop_front_empty_string_t);

  suite_add_tcase(suite, tcase_push_pop);
}

void add_peek_tests_string_t(Suite *suite) {
  TCase *tcase_peek = tcase_create("Peek");
  tcase_add_test(tcase_peek, test_peek_back_empty_string_t);
  tcase_add_test(tcase_peek, test_peek_front_empty_string_t);
  tcase_add_test(tcase_peek, test_peek_front_string_t);
  tcase_add_test(tcase_peek, test_peek_back_string_t);

  suite_add_tcase(suite, tcase_peek);
}

void add_get_value_by_index_tests_string_t(Suite *suite) {
  TCase *tcase_get_value_by_index = tcase_create("Get value from linked list");
  tcase_add_test(tcase_get_value_by_index, test_get_by_index_empty_string_t);
  tcase_add_test(tcase_get_value_by_index, test_get_by_index_string_t);
  tcase_add_test(tcase_get_value_by_index,
                 test_get_by_index_out_of_bounds_string_t);

  suite_add_tcase(suite, tcase_get_value_by_index);
}

void add_get_value_by_index_with_copy_tests_string_t(Suite *suite) {
  TCase *tcase_get_value_by_index_with_copy =
      tcase_create("Get value from linked list with copy");
  tcase_add_test(tcase_get_value_by_index_with_copy,
                 test_get_by_index_with_copy_from_linked_list_empty_list);
  tcase_add_test(tcase_get_value_by_index_with_copy,
                 test_get_by_index_with_copy_from_linked_list_invalid_index);
  tcase_add_test(tcase_get_value_by_index_with_copy,
                 test_get_by_index_with_copy_from_linked_list_valid_index);

  suite_add_tcase(suite, tcase_get_value_by_index_with_copy);
}

// Add more functions for the remaining test cases...

void add_find_in_linked_list_tests_string_t(Suite *suite) {
  TCase *tcase_find_in_linked_list = tcase_create("Find in linked list");
  tcase_add_test(tcase_find_in_linked_list,
                 test_find_in_linked_list_empty_list);
  tcase_add_test(tcase_find_in_linked_list,
                 test_find_in_linked_list_first_occurrence);
  tcase_add_test(tcase_find_in_linked_list,
                 test_find_in_linked_list_valid_data);
  tcase_add_test(tcase_find_in_linked_list,
                 test_find_in_linked_list_invalid_data);
  tcase_add_test(tcase_find_in_linked_list,
                 test_find_in_linked_list_last_occurrence);
  suite_add_tcase(suite, tcase_find_in_linked_list);
}

void add_r_find_in_linked_list_tests_string_t(Suite *suite) {
  TCase *tcase_r_find_in_linked_list = tcase_create("R find in linked list");
  tcase_add_test(tcase_r_find_in_linked_list,
                 test_r_find_in_linked_list_empty_list);
  tcase_add_test(tcase_r_find_in_linked_list,
                 test_r_find_in_linked_list_first_occurrence);
  tcase_add_test(tcase_r_find_in_linked_list,
                 test_r_find_in_linked_list_valid_data);
  tcase_add_test(tcase_r_find_in_linked_list,
                 test_r_find_in_linked_list_invalid_data);
  tcase_add_test(tcase_r_find_in_linked_list,
                 test_r_find_in_linked_list_last_occurrence);
  suite_add_tcase(suite, tcase_r_find_in_linked_list);
}

void add_get_size_tests_string_t(Suite *suite) {
  TCase *tcase_get_size = tcase_create("Get size of linked list");
  tcase_add_test(tcase_get_size, test_get_size_of_linked_list_string_t);
  suite_add_tcase(suite, tcase_get_size);
}

void add_contains_tests_string_t(Suite *suite) {
  TCase *tcase_contains = tcase_create("Contains in linked list");
  tcase_add_test(tcase_contains,
                 test_contains_in_linked_list_string_t_element_found);
  tcase_add_test(tcase_contains,
                 test_contains_in_linked_list_string_t_element_not_found);
  tcase_add_test(tcase_contains,
                 test_contains_in_linked_list_string_t_empty_list);
  suite_add_tcase(suite, tcase_contains);
}

void add_count_tests_string_t(Suite* suite)
{
    TCase *tcase_count = tcase_create("Count in linked list");
  tcase_add_test(tcase_count,
                 test_count_in_linked_list_element_found_multiple_times);
  tcase_add_test(tcase_count, test_count_in_linked_list_element_found_once);
  tcase_add_test(tcase_count, test_count_in_linked_list_empty_list);
  tcase_add_test(tcase_count, test_count_in_linked_list_element_not_found);
  suite_add_tcase(suite, tcase_count);
}

// Add more functions for the remaining test cases...

void add_remove_all_from_linked_list_tests_string_t(Suite *suite) {
  TCase *tcase_remove_all_from_linked_list =
      tcase_create("Remove all from linked list");
  tcase_add_test(tcase_remove_all_from_linked_list,
                 test_remove_all_from_linked_list_empty_list);
  tcase_add_test(tcase_remove_all_from_linked_list,
                 test_remove_all_from_linked_list_invalid_data);
  tcase_add_test(tcase_remove_all_from_linked_list,
                 test_remove_all_from_linked_list_valid_data);
  tcase_add_test(tcase_remove_all_from_linked_list,
                 test_remove_all_from_linked_list_last_occurrence);
  tcase_add_test(tcase_remove_all_from_linked_list,
                 test_remove_all_from_linked_list_first_occurrence);
  suite_add_tcase(suite, tcase_remove_all_from_linked_list);
}

void add_remove_from_linked_list_tests_string_t(Suite *suite) {
  TCase *tcase_remove_from_linked_list =
      tcase_create("Remove from linked list");
  tcase_add_test(tcase_remove_from_linked_list,
                 test_remove_from_linked_list_empty_list);
  tcase_add_test(tcase_remove_from_linked_list,
                 test_remove_from_linked_list_first_occurrence);
  tcase_add_test(tcase_remove_from_linked_list,
                 test_remove_from_linked_list_last_occurrence);
  tcase_add_test(tcase_remove_from_linked_list,
                 test_remove_from_linked_list_invalid_data);
  tcase_add_test(tcase_remove_from_linked_list,
                 test_remove_from_linked_list_valid_data);
  suite_add_tcase(suite, tcase_remove_from_linked_list);
}

void add_remove_by_index_tests_string_t(Suite* suite)
{
  TCase *tcase_remove_by_index =
      tcase_create("Remove by index from linked list");
  tcase_add_test(tcase_remove_by_index,
                 test_remove_by_index_from_linked_list_empty_list);
  tcase_add_test(tcase_remove_by_index,
                 test_remove_by_index_from_linked_list_invalid_index);
  tcase_add_test(tcase_remove_by_index,
                 test_remove_by_index_from_linked_list_valid_index);
  tcase_add_test(tcase_remove_by_index,
                 test_remove_by_index_from_linked_list_first_index);
  tcase_add_test(tcase_remove_by_index,
                 test_remove_by_index_from_linked_list_last_index);

  suite_add_tcase(suite, tcase_remove_by_index);
}



// Add more functions for the remaining test cases...


Suite *create_test_suite_linked_list_string_t(void) {
  Suite *suite = suite_create("Linked list string_t tests_string_t");

  // Add the test cases to the suite
  add_push_pop_tests_string_t(suite);
  add_peek_tests_string_t(suite);
  add_get_value_by_index_tests_string_t(suite);
  add_get_value_by_index_with_copy_tests_string_t(suite);
  add_get_size_tests_string_t(suite);
  add_contains_tests_string_t(suite);
  add_count_tests_string_t(suite);
  add_remove_from_linked_list_tests_string_t(suite);
  add_remove_by_index_tests_string_t(suite);
  add_remove_all_from_linked_list_tests_string_t(suite);
  add_find_in_linked_list_tests_string_t(suite);
  add_r_find_in_linked_list_tests_string_t(suite);

  return suite;
}
#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"
// Sample tests
Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);

// My tests

// init_c_string();
Status test_apereira_init_c_string_NULL_input(char* buffer, int length);
Status test_apereira_init_c_string_blank_string(char* buffer, int length);
Status test_apereira_init_c_string_proper_size_and_capacity(char* buffer, int length);
Status test_apereira_init_c_string_long_string_returns_proper_size_and_cap(char* buffer, int length);

// get_capacity(0)
Status test_apereira_get_capacity_NULL_input(char* buffer, int length);

// get_size(0)
Status test_apereira_get_size_NULL_input(char* buffer, int length);

// my_string_compare()
Status test_apereira_compare_left_smaller_returns_negative(char* buffer, int length);
Status test_apereira_compare_left_larger_returns_positive(char* buffer, int length);
Status test_apereira_compare_left_long_right_short(char* buffer, int length);

// my_string_extraction(0)
Status test_apereira_extraction_leading_whitespace(char* buffer, int length);
Status test_apereira_extraction_non_spacechar_whitespace_between_words(char* buffer, int length);
Status test_apereira_extraction_works_for_str_that_was_init_c_string(char* buffer, int length);

// my_string_push_back
Status test_apereira_push_back_non_alpha(char* buffer, int length);
Status test_apereira_push_back_resize_when_str_full(char* buffer, int length);

// my_string_pop_back
Status test_apereira_pop_back_NULL_input(char* buffer, int length);
Status test_apereira_pop_back_empty_str(char* buffer, int length);

// my_string_at
Status test_apereira_at_negative_idx(char* buffer, int length);
Status test_apereira_at_out_of_range(char* buffer, int length);

// my_string_c_str
Status test_apereira_c_str_NULL_input(char* buffer, int length);
Status test_apereira_c_str_same_size(char* buffer, int length);
Status test_apereira_c_str_print_test(char* buffer, int length);

// my_string_concat
Status test_apereira_NULL_input_left_or_right_or_both(char* buffer, int length);
Status test_apereira_return_fail_when_left_too_small(char* buffer, int length);


#endif

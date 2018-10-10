#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
	Status(*tests[])(char*, int) =
	{
    test_my_string_assignment_and_destroy
	};
	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	int i;
	char buffer[800];
	int success_count = 0;
	int failure_count = 0;
	for (i = 0; i<number_of_functions; i++)
	{
		if (tests[i](buffer, 800) == FAILURE)
		{
			printf("FAILED: Test %d failed miserably\n", i);
			printf("\t%s\n", buffer);
			failure_count++;
		}
		else
		{
			printf("PASS: Test %d passed\n", i);
			printf("%s\n", buffer);
			success_count++;
		}
	}
	printf("\nTotal number of tests: %d\n", number_of_functions);
	printf("%d/%d Pass, %d/%d Failure\n", success_count,
		number_of_functions, failure_count, number_of_functions);

	return 0;
}

/* LAB 5
test_init_default_returns_nonNULL,
test_get_size_on_init_default_returns_0,
test_apereira_init_c_string_blank_string,
test_apereira_init_c_string_proper_size_and_capacity,
test_apereira_init_c_string_long_string_returns_proper_size_and_cap,
test_apereira_compare_left_smaller_returns_negative,
test_apereira_compare_left_larger_returns_positive,
test_apereira_compare_left_long_right_short_returns_positive,
test_apereira_compare_two_matching_long_strings,
test_apereira_extraction_leading_whitespace,
test_apereira_extraction_non_spacechar_whitespace_between_words,
test_apereira_extraction_works_for_str_that_was_init_c_string,
test_apereira_push_back_non_alpha,
test_apereira_push_back_resize_when_str_full,
test_apereira_pop_back_empty_str,
test_apereira_pop_back_too_many_times,
test_apereira_at_negative_idx,
test_apereira_at_out_of_range,
test_apereira_at_success_case,
test_apereira_c_str_same_as_original,
test_apereira_concat_return_fail_when_left_too_small,
test_apereira_concat_success_case,
test_apereira_empty_failure_case,
test_apereira_empty_success_case,
test_apereira_compare_success_with_init_default_and_init_c_str
*/

/* Lab 6

*/

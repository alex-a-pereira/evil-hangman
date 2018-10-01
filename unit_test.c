#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
	Status(*tests[])(char*, int) =
	{
		test_init_default_returns_nonNULL,
		test_get_size_on_init_default_returns_0,
		test_apereira_init_c_string_blank_string,
		test_apereira_init_c_string_proper_size_and_capacity,
		test_apereira_init_c_string_long_string_returns_proper_size_and_cap,
		test_apereira_compare_left_smaller_returns_negative,
		test_apereira_compare_left_larger_returns_positive,
		test_apereira_compare_left_long_right_short,
		test_apereira_extraction_leading_whitespace,
		test_apereira_extraction_non_spacechar_whitespace_between_words,
		test_apereira_extraction_works_for_str_that_was_init_c_string,

	};
	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	int i;
	char buffer[500];
	int success_count = 0;
	int failure_count = 0;
	for (i = 0; i<number_of_functions; i++)
	{
		if (tests[i](buffer, 500) == FAILURE)
		{
			printf("FAILED: Test %d failed miserably\n", i);
			printf("\t%s\n", buffer);
			failure_count++;
		}
		else
		{
			// printf("PASS: Test %d passed\n", i);
			// printf("\t%s\n", buffer);
			success_count++;
		}
	}
	printf("Total number of tests: %d\n", number_of_functions);
	printf("%d/%d Pass, %d/%d Failure\n", success_count,
		number_of_functions, failure_count, number_of_functions);
	return 0;
}

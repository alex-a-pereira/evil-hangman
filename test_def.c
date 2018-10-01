#include <stdio.h>
#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if (hString == NULL)
	{
		my_string_destroy(&hString);
		strncpy(buffer, "test_init_default_returns_nonNULL\n"
			"my_string_init_default returns NULL", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy(&hString);
		strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
		return SUCCESS;
	}
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if (my_string_get_size(hString) != 0)
	{
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
			"Did not receive 0 from get_size after init_default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
			, length);
	}
	my_string_destroy(&hString);
	return status;
}

// init_c_string();
Status test_apereira_init_c_string_blank_string(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	char* c_string = "";

	hString = my_string_init_c_string(c_string);
	if (my_string_get_size(hString) == 0) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_init_c_string_blank_string \n", length);
	} else {
		status = FAILURE;
		printf("Expected my_string to be size 0, but got size of: %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_apereira_init_c_string_blank_string \nDid not receive 0 from get_size after init_c_string w/ a blank c_string\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_apereira_init_c_string_proper_size_and_capacity(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	char* c_string = "test";

	hString = my_string_init_c_string(c_string);

	if ((my_string_get_size(hString) == 4) && (my_string_get_capacity(hString) == 5)) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_init_c_string_proper_size_and_capacity \n", length);
	} else {
		status = FAILURE;
		printf("Expected my_string to be size of 4 and capacity of 5, but got size of: %d and cap of: %d\n", my_string_get_size(hString), my_string_get_capacity(hString));
		strncpy(buffer, "test_apereira_init_c_string_proper_size_and_capacity \nDid not receive 4 from get_size and 5 from get_capacity after init_c_string w/ an input of \"test\" c_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_apereira_init_c_string_long_string_returns_proper_size_and_cap(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	char* c_string = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	hString = my_string_init_c_string(c_string);

	if ((my_string_get_size(hString) == 52) && (my_string_get_capacity(hString) == 53)) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_init_c_string_long_string_returns_proper_size_and_cap \n", length);
	} else {
		status = FAILURE;
		printf("Expected my_string to be size of 52 and capacity of 53, but got size of: %d and cap of: %d\n", my_string_get_size(hString), my_string_get_capacity(hString));
		strncpy(buffer, "test_apereira_init_c_string_long_string_returns_proper_size_and_cap \nDid not receive 52 from get_size and 53 from get_capacity after init_c_string w/ an input of \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\" c_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

// my_string_compare()
Status test_apereira_compare_left_smaller_returns_negative(char* buffer, int length) {
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	char* c_string1 = "aaaabbbb";
	char* c_string2 = "bbbbaaaa";

	hString1 = my_string_init_c_string(c_string1);
	hString2 = my_string_init_c_string(c_string2);

	int result = my_string_compare(hString1, hString2);

	if (result < 0) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_compare_left_smaller_returns_negative", length);
	} else {
		status = FAILURE;
		printf("Expected my_string_compare to return a negative int with inputs of \"aaaabbbb\" and \"bbbbaaaa\" but instead received: %d\n", result);
		strncpy(buffer, "test_apereira_compare_left_smaller_returns_negative \n did not receive a negative int from my_string_compare with inputs of \"aaaabbbb\" and \"bbbbaaaa\"", length);
	}

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;

}
Status test_apereira_compare_left_larger_returns_positive(char* buffer, int length) {
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;
	char* c_string1 = "bbbbaaaa";
	char* c_string2 = "aaaabbbb";

	hString1 = my_string_init_c_string(c_string1);
	hString2 = my_string_init_c_string(c_string2);

	int result = my_string_compare(hString1, hString2);

	if (result > 0) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_compare_left_larger_returns_positive", length);
	} else {
		status = FAILURE;
		printf("test_apereira_compare_left_larger_returns_positive \n did not receive a positive int from my_string_compare with inputs of \"bbbbaaaa\" and \"aaaabbbb\", instead got %d", result);

		strncpy(buffer, "test_apereira_compare_left_larger_returns_positive \n did not receive a positive int from my_string_compare with inputs of \"bbbbaaaa\" and \"aaaabbbb\"", length);
printf("\n\nmade it this far\n\n");
	}

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status test_apereira_compare_left_long_right_short(char* buffer, int length) {
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	// test here
	char* c_string1 = "aaaabbbb";
	char* c_string2 = "aaaabbbb";

	hString1 = my_string_init_c_string(c_string1);
	hString2 = my_string_init_c_string(c_string2);

	int result = my_string_compare(hString1, hString2);

	if (result == 0) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_compare_left_long_right_short", length);
	} else {
		status = FAILURE;
		printf("test_apereira_compare_left_long_right_short \n did not receive positive int from my_string_compare with inputs of \"aaaabbbbBASJDASDASDKKASDSDASADSDA\" and \"aaaabbbb\", instead got %d", result);
		strncpy(buffer, "test_apereira_compare_left_long_right_short \n did not receive positive int from my_string_compare with inputs of \"aaaabbbbBASJDASDASDKKASDSDASADSDA\" and \"aaaabbbb\"", length);
	}

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

// my_string_extraction(0)
Status test_apereira_extraction_leading_whitespace(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	FILE *fp = fopen("./test_txt_files/leadingWhitespace.txt", "r");

	Status stat = my_string_extraction(hString, fp);

	if (stat == SUCCESS) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_extraction_leading_whitespace", length);
	} else {
		status = FAILURE;
		printf("test_apereira_extraction_leading_whitespace \n did not receive SUCCESS from my_string_extraction with inputs of leadingWhitespace.txt, instead got %d", stat);
		strncpy(buffer, "test_apereira_extraction_leading_whitespace \n did not receive SUCCESS from my_string_extraction with inputs of leadingWhitespace.txt", length);
	}
	fclose(fp);
	my_string_destroy(&hString);
	return status;
}

Status test_apereira_extraction_non_spacechar_whitespace_between_words(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	// test here
	FILE *fp = fopen("./test_txt_files/nonspace_whitespace.txt", "r");
	Status stat = my_string_extraction(hString, fp);

	if (stat == SUCCESS) {
		status = SUCCESS;
		strncpy(buffer, "FUNCNAME", length);
	} else {
		status = FAILURE;
		printf("test_apereira_extraction_non_spacechar_whitespace_between_words \n did not receive SUCCESS from my_string_extraction with inputs of nonspace_whitespace.txt, instead got %d", stat);
		strncpy(buffer, "test_apereira_extraction_non_spacechar_whitespace_between_words \n did not receive SUCCESS from my_string_extraction with inputs of nonspace_whitespace.txt", length);
	}
	fclose(fp);
	my_string_destroy(&hString);
	return status;
}

Status test_apereira_extraction_works_for_str_that_was_init_c_string(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	FILE *fp = fopen("./test_txt_files/simple.txt", "r");
	char* c_string1 = "loremipsumloremipsumloremipsum";

	hString = my_string_init_c_string(c_string1);
	Status stat = my_string_extraction(hString, fp);

	if (stat == SUCCESS) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_extraction_works_for_str_that_was_init_c_string", length);
	} else {
		status = FAILURE;
		printf("test_apereira_extraction_works_for_str_that_was_init_c_string \n did not receive SUCCES from my_string_extraction with inputs of a my_string that was initted w/ my_string_init_c_string and simple.txt, instead got %d", stat);
		strncpy(buffer, "test_apereira_extraction_works_for_str_that_was_init_c_string \n did not receive SUCCES from my_string_extraction with inputs of a my_string that was initted w/ my_string_init_c_string and simple.txt", length);
	}
	fclose(fp);
	my_string_destroy(&hString);
	return status;
}

// // my_string_push_back
// Status test_apereira_push_back_non_alpha(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }
//
// Status test_apereira_push_back_resize_when_str_full(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }
//
// // my_string_pop_back
// Status test_apereira_pop_back_NULL_input(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }
//
// Status test_apereira_pop_back_empty_str(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }
//
// // my_string_at
// Status test_apereira_at_negative_idx(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }
//
// Status test_apereira_at_out_of_range(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }
//
// // my_string_c_str
// Status test_apereira_c_str_NULL_input(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }
//
// Status test_apereira_c_str_same_size(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }
//
// Status test_apereira_c_str_print_test(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }
//
// // my_string_concat
// Status test_apereira_NULL_input_left_or_right_or_both(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }
//
// Status test_apereira_return_fail_when_left_too_small(char* buffer, int length) {
// 	MY_STRING hString = NULL;
// 	Status status;
//
// 	// test here
//
// 	if (1) {
// 		status = SUCCESS;
// 		strncpy(buffer, "FUNCNAME", length);
// 	} else {
// 		status = FAILURE;
// 		printf("FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS, instead got ACTUALRET", result);
// 		strncpy(buffer, "FUNCNAME \n did not receive EXPECTEDRET from TEST with inputs of INPUTS", length);
// 	}
// }

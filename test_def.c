#include <stdio.h>
#include <string.h>
#include "unit_test.h"
Status test_init_default_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if (hString == NULL)
	{
		my_string_destroy((Item*)&hString);
		strncpy(buffer, "test_init_default_returns_nonNULL\n"
			"my_string_init_default returns NULL", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy((Item*)&hString);
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
	my_string_destroy((Item*)&hString);
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
	}
	else {
		status = FAILURE;
		printf("Expected my_string to be size 0, but got size of: %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_apereira_init_c_string_blank_string \nDid not receive 0 from get_size after init_c_string w/ a blank c_string\n", length);
	}
	my_string_destroy((Item*)&hString);
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
	}
	else {
		status = FAILURE;
		printf("Expected my_string to be size of 4 and capacity of 5, but got size of: %d and cap of: %d\n", my_string_get_size(hString), my_string_get_capacity(hString));
		strncpy(buffer, "test_apereira_init_c_string_proper_size_and_capacity \nDid not receive 4 from get_size and 5 from get_capacity after init_c_string w/ an input of \"test\" c_string\n", length);
	}

	my_string_destroy((Item*)&hString);
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
	}
	else {
		status = FAILURE;
		printf("Expected my_string to be size of 52 and capacity of 53, but got size of: %d and cap of: %d\n", my_string_get_size(hString), my_string_get_capacity(hString));
		strncpy(buffer, "test_apereira_init_c_string_long_string_returns_proper_size_and_cap \nDid not receive 52 from get_size and 53 from get_capacity after init_c_string w/ an input of \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\" c_string\n", length);
	}

	my_string_destroy((Item*)&hString);
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
	}
	else {
		status = FAILURE;
		printf("Expected my_string_compare to return a negative int with inputs of \"aaaabbbb\" and \"bbbbaaaa\" but instead received: %d\n", result);
		strncpy(buffer, "test_apereira_compare_left_smaller_returns_negative \n did not receive a negative int from my_string_compare with inputs of \"aaaabbbb\" and \"bbbbaaaa\"", length);
	}

	my_string_destroy((Item*)&hString1);
	my_string_destroy((Item*)&hString2);
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
	}
	else {
		status = FAILURE;
		printf("test_apereira_compare_left_larger_returns_positive \n did not receive a positive int from my_string_compare with inputs of \"bbbbaaaa\" and \"aaaabbbb\", instead got %d", result);

		strncpy(buffer, "test_apereira_compare_left_larger_returns_positive \n did not receive a positive int from my_string_compare with inputs of \"bbbbaaaa\" and \"aaaabbbb\"", length);
		printf("\n\nmade it this far\n\n");
	}

	my_string_destroy((Item*)&hString1);
	my_string_destroy((Item*)&hString2);
	return status;
}

Status test_apereira_compare_left_long_right_short_returns_positive(char* buffer, int length) {
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	char* c_string1 = "aaaabbbbzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
	char* c_string2 = "aaaabbbb";

	hString1 = my_string_init_c_string(c_string1);
	hString2 = my_string_init_c_string(c_string2);

	int result = my_string_compare(hString1, hString2);

	if (result > 0) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_compare_left_long_right_short", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_compare_left_long_right_short \n did not receive positive int from my_string_compare with inputs of \"aaaabbbbBASJDASDASDKKASDSDASADSDA\" and \"aaaabbbb\", instead got %d", result);
		strncpy(buffer, "test_apereira_compare_left_long_right_short \n did not receive positive int from my_string_compare with inputs of \"aaaabbbbBASJDASDASDKKASDSDASADSDA\" and \"aaaabbbb\"", length);
	}

	my_string_destroy((Item*)&hString1);
	my_string_destroy((Item*)&hString2);
	return status;
}

Status test_apereira_compare_two_matching_long_strings(char *buffer, int length) {
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;
	char *c_string1 = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
	char *c_string2 = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";

	hString1 = my_string_init_c_string(c_string1);
	hString2 = my_string_init_c_string(c_string2);

	Status stat = my_string_compare(hString1, hString2);

	if (stat == 0) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_compare_two_matching_long_strings", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_compare_two_matching_long_strings \n did not receive SUCCESS with inputs of two valid, long, and exactly matching my_string objects");
		strncpy(buffer, "test_apereira_compare_two_matching_long_strings \n did not receive SUCCESS with inputs of two valid, long, and exactly matching my_string objects", length);
	}
	my_string_destroy((Item*)&hString1);
	my_string_destroy((Item*)&hString2);
	return status;
}
//
// my_string_extraction(0)
//
Status test_apereira_extraction_leading_whitespace(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_default();
	FILE *fp = fopen("./test_txt_files/leadingWhitespace.txt", "r");

	Status stat = my_string_extraction(hString, fp);

	if (stat == SUCCESS) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_extraction_leading_whitespace", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_extraction_leading_whitespace \n did not receive SUCCESS from my_string_extraction with inputs of leadingWhitespace.txt, instead got %d", stat);
		strncpy(buffer, "test_apereira_extraction_leading_whitespace \n did not receive SUCCESS from my_string_extraction with inputs of leadingWhitespace.txt", length);
	}
	fclose(fp);
	my_string_destroy((Item*)&hString);
	return status;
}

Status test_apereira_extraction_non_spacechar_whitespace_between_words(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	// test here
	FILE *fp = fopen("./test_txt_files/nonspace_whitespace.txt", "r");
	Status stat = my_string_extraction(hString, fp);

	if (stat == SUCCESS) {
		status = SUCCESS;
		strncpy(buffer, "FUNCNAME", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_extraction_non_spacechar_whitespace_between_words \n did not receive SUCCESS from my_string_extraction with inputs of nonspace_whitespace.txt, instead got %d", stat);
		strncpy(buffer, "test_apereira_extraction_non_spacechar_whitespace_between_words \n did not receive SUCCESS from my_string_extraction with inputs of nonspace_whitespace.txt", length);
	}
	fclose(fp);
	my_string_destroy((Item*)&hString);
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
	}
	else {
		status = FAILURE;
		printf("test_apereira_extraction_works_for_str_that_was_init_c_string \n did not receive SUCCES from my_string_extraction with inputs of a my_string that was initted w/ my_string_init_c_string and simple.txt, instead got %d", stat);
		strncpy(buffer, "test_apereira_extraction_works_for_str_that_was_init_c_string \n did not receive SUCCES from my_string_extraction with inputs of a my_string that was initted w/ my_string_init_c_string and simple.txt", length);
	}
	fclose(fp);
	my_string_destroy((Item*)&hString);
	return status;
}

// my_string_push_back
Status test_apereira_push_back_non_alpha(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_default();

	Status stat = my_string_push_back(hString, '`');

	if (stat == FAILURE) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_push_back_non_alpha", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_push_back_non_alpha \n did not receive FAILURE from my_string_push_back with inputs of a my_string that was initted w/ my_string_init_default and a backtick ` char, instead got %d", stat);
		strncpy(buffer, "test_apereira_push_back_non_alpha \n did not receive SUCCESS from my_string_extraction with inputs of a my_string that was initted w/ my_string_init_default and a backtick ` char", length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}
Status test_apereira_push_back_resize_when_str_full(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	// default size = 0, default capacity = 7
	hString = my_string_init_default();

	Status stat = my_string_push_back(hString, 'a');
	stat = my_string_push_back(hString, 'a');
	stat = my_string_push_back(hString, 'a');
	stat = my_string_push_back(hString, 'a');
	stat = my_string_push_back(hString, 'a');
	stat = my_string_push_back(hString, 'a');
	stat = my_string_push_back(hString, 'a');

	int new_size = my_string_get_size(hString);
	int new_capacity = my_string_get_capacity(hString);

	if ((stat == SUCCESS) && (new_size == 7) && (new_capacity >= 13)) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_push_back_resize_when_str_full", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_push_back_resize_when_str_full \n did not receive SUCCESS from my_string_push_back or did not receive properly resize the my_string when seven 'a' chars were push_back'd successively");
		strncpy(buffer, "test_apereira_push_back_resize_when_str_full \n did not receive SUCCESS from my_string_push_back or did not receive properly resize the my_string when seven 'a' chars were push_back'd successively", length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}

// my_string_pop_back

Status test_apereira_pop_back_empty_str(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	// default size = 0, default capacity = 7
	hString = my_string_init_default();

	Status stat = my_string_pop_back(hString);
	if (stat == FAILURE) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_pop_back_empty_str", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_pop_back_empty_str \n did not receive SUCCESS from my_string_pop_back when an empty my_string_init_default'd was passed into it");
		strncpy(buffer, "test_apereira_pop_back_empty_str \n did not receive SUCCESS from my_string_pop_back when an empty my_string_init_default'd was passed into it", length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}

Status test_apereira_pop_back_too_many_times(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("ABC");

	Status stat = my_string_pop_back(hString);
	stat = my_string_pop_back(hString);
	stat = my_string_pop_back(hString);
	stat = my_string_pop_back(hString);

	if (stat == FAILURE) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_pop_back_too_many_times", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_pop_back_too_many_times \n did not receive FAILURE after trying to pop 4 chars from the 3 char long string 'ABC'");
		strncpy(buffer, "test_apereira_pop_back_too_many_times \n did not receive FAILURE after trying to pop 4 chars from the 3 char long string 'ABC'", length);
	}
	my_string_destroy((Item*)&hString);
	return status;

}

// my_string_at
Status test_apereira_at_negative_idx(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	char *c_string = "BIGTEST";
	// default size = 0, default capacity = 7
	hString = my_string_init_c_string(c_string);

	char *p_char = my_string_at(hString, -1);
	if (p_char == NULL) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_at_negative_idx", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_at_negative_idx \n did not receive NULL from my_string_at with inputs of a valid hMy_String and an index of -1");
		strncpy(buffer, "test_apereira_at_negative_idx \n did not receive NULL from my_string_at with inputs of a valid hMy_String and an index of -1", length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}


Status test_apereira_at_out_of_range(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	char *c_string = "BIGTEST";
	hString = my_string_init_c_string(c_string);

	char *p_char = my_string_at(hString, 7);
	if (p_char == NULL) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_at_out_of_range", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_at_out_of_range \n did not receive NULL from my_string_at with inputs of a valid hMy_String that contained 7 chars and an index of 7");
		strncpy(buffer, "test_apereira_at_out_of_range \n did not receive NULL from my_string_at with inputs of a valid hMy_String that contained 7 chars and an index of 7", length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}

Status test_apereira_at_success_case(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	char *c_string = "BIGTEST";
	hString = my_string_init_c_string(c_string);

	char *p_char = my_string_at(hString, 6);

	if ((p_char != NULL) && (*p_char == 'T')) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_at_success_case", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_at_success_case \n did not receive a pointer to char 'T' from my_string_at with inputs of a valid hMy_String that contained string 'BIG TEST' that's 7 chars long and an index of 6");
		strncpy(buffer, "test_apereira_at_success_case \n did not receive a pointer to char 'T' from my_string_at with inputs of a valid hMy_String that contained string 'BIG TEST' that's 7 chars long and an index of 6", length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}

// my_string_c_str
Status test_apereira_c_str_same_as_original(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	char *c_string = "cStringCool";
	int original_length = 11;
	hString = my_string_init_c_string(c_string);

	char *new_string = my_string_c_str(hString);

	// originally succes, will be set to failure if any char is not the same the original string
	Status stat = SUCCESS;
	for (int i = 0; i < original_length; i++) {
		if (new_string[i] != c_string[i]) {
			stat = FAILURE;
		}
	}

	if (stat == SUCCESS) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_c_str_same_as_original", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_c_str_same_as_original \n did not receive a pointer to char array  that exactly matched the original c string it was initt'd with from my_string_c_str");
		strncpy(buffer, "test_apereira_c_str_same_as_original \n did not receive a pointer to char array  that exactly matched the original c string it was initt'd with from my_string_c_str", length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}

// my_string_concat
Status test_apereira_concat_return_fail_when_left_too_small(char* buffer, int length) {
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	char *c_string1 = "test1";
	char *c_string2 = "test2";

	hString1 = my_string_init_c_string(c_string1);
	hString2 = my_string_init_c_string(c_string2);

	Status stat = my_string_concat(hString1, hString2);

	if (stat == FAILURE) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_concat_return_fail_when_left_too_small", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_concat_return_fail_when_left_too_small \n did not receive FAILURE with inputs of valid hMy_String1 that contained string 'test1' that has a capacity of 6, and valid hMy_string2 with a size of 5");
		strncpy(buffer, "test_apereira_concat_return_fail_when_left_too_small \n did not receive FAILURE with inputs of valid hMy_String1 that contained string 'test1' that has a capacity of 6, and valid hMy_string2 with a size of 5", length);
	}
	my_string_destroy((Item*)&hString1);
	my_string_destroy((Item*)&hString2);
	return status;
}

Status test_apereira_concat_success_case(char*buffer, int length) {
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	char *c_string2 = "str2";

	hString1 = my_string_init_default();
	hString2 = my_string_init_c_string(c_string2);

	Status stat = my_string_concat(hString1, hString2);

	if (stat == SUCCESS) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_concat_success_case", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_concat_success_case \n did not receive SUCCESS with inputs of valid hMy_String1 an empty string that has a capacity of 7, and valid hMy_string2 with a size of 4");
		strncpy(buffer, "test_apereira_concat_success_case \n did not receive SUCCESS with inputs of valid hMy_String1 an empty string that has a capacity of 7, and valid hMy_string2 with a size of 4", length);
	}
	my_string_destroy((Item*)&hString1);
	my_string_destroy((Item*)&hString2);
	return status;
}

Status test_apereira_empty_failure_case(char *buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_string("abc");

	Boolean stat = my_string_empty(hString);
	if (stat == FALSE) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_empty_failure_case", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_empty_failure_case \n did not receive FALSE from my_string_empty when an empty my_string_init_c_str was passed into it");
		strncpy(buffer, "test_apereira_empty_failure_case \n did not receive FALSE from my_string_empty when an empty my_string_init_c_str was passed into it", length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}

Status test_apereira_empty_success_case(char *buffer, int length) {
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_default();

	Boolean stat = my_string_empty(hString);
	if (stat == TRUE) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_concat_success_case", length);
	}
	else {
		status = FAILURE;
		printf("test_apereira_empty_success_case \n did not receive TRUE from my_string_empty when an empty my_string_init_default'd was passed into it");
		strncpy(buffer, "test_apereira_empty_success_case \n did not receive TRUE from my_string_empty when an empty my_string_init_default'd was passed into it", length);
	}
	my_string_destroy((Item*)&hString);
	return status;
}

// normal user use case, multiple functions
Status test_apereira_compare_success_with_init_default_and_init_c_str(char *buffer, int length) {
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;
	char *c_str2 = "abcdefghijklmnopqrstuvwxyz";

	hString1 = my_string_init_default();
	hString2 = my_string_init_c_string(c_str2);

	char start_char = 'a';
	for (int i = 0; i < 26; i++) {
		my_string_push_back(hString1, (start_char + i));
	}

	int stat = my_string_compare(hString1, hString2);

	if (stat == 0) {
		status = SUCCESS;
		strncpy(buffer, "test_apereira_compare_success_with_init_default_and_init_c_str", length);

	}
	else {
		status = FAILURE;
		printf("test_apereira_compare_success_with_init_default_and_init_c_str \n did not receive 0 from my_string_compare with args of a my_string init_default'd and push back'd with 26 chars a-z and a my_string init_c_str'd with a c string containing chars a-z");
		strncpy(buffer, "test_apereira_compare_success_with_init_default_and_init_c_str \n did not receive 0 from my_string_compare with args of a my_string init_default'd and push back'd with 26 chars a-z and a my_string init_c_str'd with a c string containing chars a-z", length);
	}
	my_string_destroy((Item*)&hString1);
	my_string_destroy((Item*)&hString2);
	return status;
}

// Lab 6
Status test_my_string_assignment_and_destroy(char *buffer, int length) {
	Status status;

	MY_STRING my_string_arr[100] = { NULL };
	
	my_string_arr[0] = my_string_init_c_string("COPY ME!");
	// Copy first str to each index in ARR
	for (int i = 0; i < 100; i++) {
		my_string_assignment(&my_string_arr[i], my_string_arr[0]);
	}

	for (int i = 0; i < 100; i++) {
		printf("%d: ", i + 1);
		my_string_insertion(my_string_arr[i], stdout);
		my_string_destroy(&my_string_arr[i]);
	}
	printf("\n");
	// loop over array and set stat to FAILURE if any element is not a null pointer, as there's a memory leak
	Status stat = SUCCESS;
	for (int i = 0; i < 100; i++) {
		if (my_string_arr[i] != NULL) {
			stat = FAILURE;
		}
	}
	if (stat == SUCCESS) {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_assignment_and_destroy", length);

	}
	else {
		status = FAILURE;
		printf("test_my_string_assignment_and_destroy did not contain an array of SOLELY 100 null pointers after my_string_destroy'ing every element in the array.");
		strncpy(buffer, "test_my_string_assignment_and_destroy did not contain an array of SOLELY 100 null pointers after my_string_destroy'ing every element in the array.", length);
	}
	return status;
}
#include <stdio.h>
#include <stdlib.h>
#include "./my_string.h"

int main(int argc, char* argv[]) {
	return 0;
}

// LAB 3
// MY_STRING hMy_string = NULL;
// FILE* fp;
// hMy_string = my_string_init_default();
//
// fp = fopen("./dictionary.txt", "r");
// while (my_string_extraction(hMy_string, fp))
// {
// 	if (my_string_get_size(hMy_string) == 29) {
// 		my_string_insertion(hMy_string, stdout);
// 		if (fgetc(fp) == ' ')
// 		{
// 			printf("Found a space after the string\n");
// 		}
// 	}
// }
//
// my_string_destroy(&hMy_string);
// fclose(fp);
// return 0;

// Lab 4
// MY_STRING hMy_string1 = NULL;
// hMy_string1 = my_string_init_default();
//
// MY_STRING hMy_string2 = NULL;
// hMy_string2 = my_string_init_default();
//
// printf("my_string_1 is empty? %d\n", my_string_empty(hMy_string1));
// printf("my_string_2 is empty? %d\n", my_string_empty(hMy_string2));
//
// printf("\nInit strings (blanks should print because no data is in either strings)\n");
// my_string_insertion(hMy_string1, stdout);
// my_string_insertion(hMy_string2, stdout);
//
// printf("\nPush back chars to each string\n");
// my_string_push_back(hMy_string1, 'a');
// my_string_push_back(hMy_string2, 'x');
// my_string_insertion(hMy_string1, stdout);
// my_string_insertion(hMy_string2, stdout);
// printf("\n");
// my_string_push_back(hMy_string1, 'b');
// my_string_push_back(hMy_string2, 'y');
// my_string_insertion(hMy_string1, stdout);
// my_string_insertion(hMy_string2, stdout);
// printf("\n");
// my_string_push_back(hMy_string1, 'c');
// my_string_push_back(hMy_string2, 'z');
// my_string_insertion(hMy_string1, stdout);
// my_string_insertion(hMy_string2, stdout);
//
// printf("check if empty after after push_backs:\n");
// printf("my_string_1 is empty? %d\n", my_string_empty(hMy_string1));
// printf("my_string_2 is empty? %d\n", my_string_empty(hMy_string2));
//
// printf("\nPop back all chars from hMy_string2 (last line should be blank bc no chars)\n");
// my_string_insertion(hMy_string2, stdout);
// my_string_pop_back(hMy_string2);
// my_string_insertion(hMy_string2, stdout);
// my_string_pop_back(hMy_string2);
// my_string_insertion(hMy_string2, stdout);
// my_string_pop_back(hMy_string2);
// my_string_insertion(hMy_string2, stdout);
// printf("\nPush back one char to hMy_string2\n");
// my_string_push_back(hMy_string2, 'x');
// my_string_insertion(hMy_string2, stdout);
//
// printf("\nConcat hMy_string2 into hMy_string1\n");
// my_string_concat(hMy_string1, hMy_string2);
// my_string_insertion(hMy_string1, stdout);
// printf("\nRepeat concat until hMy_string1 is full (default capacity of 7)\n");
// my_string_concat(hMy_string1, hMy_string2);
// my_string_insertion(hMy_string1, stdout);
// my_string_concat(hMy_string1, hMy_string2);
// my_string_insertion(hMy_string1, stdout);
// my_string_concat(hMy_string1, hMy_string2);
// my_string_insertion(hMy_string1, stdout);
//
// printf("\nTest print of char w/ my_string_at(hMy_string1)\n");
// char* my_c_string = my_string_c_str(hMy_string1);
// printf("my_c_string: %s\n", my_c_string);
//
// char* ch = my_string_at(hMy_string1, 4);
// printf("character at index 4: %c\n", *ch);
// ch = my_string_at(hMy_string1, 0);
// printf("character at index 0: %c\n", *ch);
//
// printf("Testing to see if the array capacity will double if pushback exceeds capacity");
// int pre_test_size = my_string_get_size(hMy_string1);
// int pre_test_capacity = my_string_get_capacity(hMy_string1);
// printf("pre_test_c_string: %s, pre size = %d, pre capacity = %d\n", my_c_string, pre_test_size, pre_test_capacity);
// my_string_push_back(hMy_string1, '1');
//
// char* test_c_string = my_string_c_str(hMy_string1);
// int test_size = my_string_get_size(hMy_string1);
// int test_capacity = my_string_get_capacity(hMy_string1);
// printf("test_c_string: %s, new size = %d, new capacity = %d\n", test_c_string, test_size, test_capacity);
//
// printf("\nTry again\n");
// my_string_push_back(hMy_string1, '2');
// my_string_push_back(hMy_string1, '3');
// my_string_push_back(hMy_string1, '4');
// my_string_push_back(hMy_string1, '5');
// my_string_push_back(hMy_string1, '6');
// test_c_string = my_string_c_str(hMy_string1);
// test_size = my_string_get_size(hMy_string1);
// test_capacity = my_string_get_capacity(hMy_string1);
// printf("test_c_string: %s, new size = %d, new capacity = %d\n", test_c_string, test_size, test_capacity);
//
// my_string_push_back(hMy_string1, '7');
// test_c_string = my_string_c_str(hMy_string1);
// test_size = my_string_get_size(hMy_string1);
// test_capacity = my_string_get_capacity(hMy_string1);
// printf("test_c_string: %s, new size = %d, new capacity = %d\n", test_c_string, test_size, test_capacity);
//
// my_string_destroy(&hMy_string1);
// my_string_destroy(&hMy_string2);
//
// return 0;

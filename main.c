#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "vector.h"

int main(int argc, char* argv[]) {
	VECTOR hVector = NULL;
	hVector = vector_init_default();

	MY_STRING hMy_string = NULL;
	hMy_string = my_string_init_default();

	FILE* fp;
	fp = fopen("./dictionary.txt", "r");

	while (my_string_extraction(hMy_string, fp))
	{
		if (my_string_get_size(hMy_string) == (22)) {
			vector_push_back(hVector, hMy_string);
		}
	}
	my_string_destroy(&hMy_string);

	vector_destroy(&hVector);
	fclose(fp);

	return 0;
}



/*
	VECTOR* vector_array[29];
	for (int i = 0; i < 29; i++) {
		VECTOR hVector = NULL;
		hVector = vector_init_default();

		MY_STRING hMy_string = NULL;
		hMy_string = my_string_init_default();

		FILE* fp;
		fp = fopen("./dictionary.txt", "r");

		while (my_string_extraction(hMy_string, fp))
		{
			if (my_string_get_size(hMy_string) == (i + 1)) {
				vector_push_back(hVector, hMy_string);
			}
		}
		my_string_destroy(&hMy_string);



		vector_array[i] = hVector;

		// vector_destroy(&hVector);
		fclose(fp);
	}

	for (int i = 0; i < 29; i++) {
		int vector_size = vector_get_size(vector_array[i]);
		printf("%d words with %d characters in them\n", vector_size, i + 1);
	}

	for (int i = 0; i < 29; i++) {
		VECTOR* vector_to_destroy = &vector_array[i];
		vector_destroy(vector_to_destroy);
	}
*/



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

/*
Lab 7 VECTORVECTOR hVector = NULL;
hVector = vector_init_default();

MY_STRING hMy_string = NULL;
hMy_string = my_string_init_default();

FILE* fp;
fp = fopen("./dictionary.txt", "r");

printf("...finding all strings in dict where str size == 22");
while (my_string_extraction(hMy_string, fp))
{
	if (my_string_get_size(hMy_string) == 22) {
		vector_push_back(hVector, hMy_string);
	}
}
my_string_destroy(&hMy_string);

int vector_size = vector_get_size(hVector);
int vector_cap = vector_get_capacity(hVector);
printf("\n\nfinal vector... size = %d, cap = %d\n\nContents are:\n", vector_size, vector_cap);

MY_STRING my_string_result = NULL;
for (int i = 0; i < vector_size; i++) {
	my_string_result = vector_at(hVector, i);
	char * c_str = my_string_c_str(my_string_result);
	printf("%s\t", c_str);
}
vector_destroy(&hVector);
fclose(fp);

return 0;
VECTOR hVector = NULL;
hVector = vector_init_default();

MY_STRING hMy_string = NULL;
hMy_string = my_string_init_default();

FILE* fp;
fp = fopen("./dictionary.txt", "r");

printf("...finding all strings in dict where str size == 22");
while (my_string_extraction(hMy_string, fp))
{
	if (my_string_get_size(hMy_string) == 22) {
		vector_push_back(hVector, hMy_string);
	}
}
my_string_destroy(&hMy_string);

int vector_size = vector_get_size(hVector);
int vector_cap = vector_get_capacity(hVector);
printf("\n\nfinal vector... size = %d, cap = %d\n\nContents are:\n", vector_size, vector_cap);

MY_STRING my_string_result = NULL;
for (int i = 0; i < vector_size; i++) {
	my_string_result = vector_at(hVector, i);
	char * c_str = my_string_c_str(my_string_result);
	printf("%s\t", c_str);
}
vector_destroy(&hVector);
fclose(fp);

return 0;
*/

/*
GAME!!!!
int word_length_input(void);
int num_guesses_input(void);
VECTOR read_words_from_dict(int length);


// MAIN

int word_length;
int num_guesses;
int vector_size;
VECTOR hVector;
FILE *fp;
word_length = word_length_input();
fp = fopen("./dictionary.txt", "r");
hVector = read_words_from_dict(word_length);

// handle exception when no words of given length exist
vector_size = vector_get_size(hVector);
while (vector_size == 0) {
	printf("I'm sorry, no words of length %d exist in the English dictionary. Please choose another length between 1 and 29.\n", vector_size);
	vector_destroy(&hVector);
	word_length = word_length_input();
	hVector = read_words_from_dict(word_length);
	vector_size = vector_get_size(hVector);
}

num_guesses = num_guesses_input();


printf("\nSTART GAME!\n\n");
while (num_guesses != 0) {
	printf("You have %d guesses left.\n", num_guesses);
	printf("Used letters: @\n");
	printf("Word: -------");

	printf("\n\n");
	num_guesses--;
}




int word_length_input(void)
{
	int input, numOfConversions;
	printf("What length word do you want to play with? Enter an integer between 1 and 29: ");
	numOfConversions = scanf("%d", &input);

	while (numOfConversions == 0 || input < 1 || input > 29)
	{
		char ch;
		scanf("%c", &ch);
		while (ch != '\n')
			scanf("%c", &ch);

		printf("I'm sorry, please enter an integer between 0 and 29: ");
		numOfConversions = scanf("%d", &input);
	}
	return input;
}

int num_guesses_input(void) {
	int input, numOfConversions;
	printf("How many guesses would you like to have? Enter a positive integer: ");
	numOfConversions = scanf("%d", &input);

	while (numOfConversions == 0 || input < 1)
	{
		char ch;
		scanf("%c", &ch);
		while (ch != '\n') {
			scanf("%c", &ch);
		}

		printf("I'm sorry, please enter an integer greater than 1: ");
		numOfConversions = scanf("%d", &input);
	}
	return input;
}

VECTOR read_words_from_dict(int length) {
	VECTOR hVector = NULL;
	hVector = vector_init_default();

	MY_STRING hMy_string = NULL;
	hMy_string = my_string_init_default();

	FILE *fp = fopen("./dictionary.txt", "r");

	printf("...finding all strings in dict where str size == %d", length);
	while (my_string_extraction(hMy_string, fp))
	{
		if (my_string_get_size(hMy_string) == length) {
			vector_push_back(hVector, hMy_string);
		}
	}
	my_string_destroy(&hMy_string);

	int vector_size = vector_get_size(hVector);
	int vector_cap = vector_get_capacity(hVector);
	printf("\n\nfinal vector... size = %d, cap = %d\n\nContents are:\n", vector_size, vector_cap);

	MY_STRING my_string_result = NULL;
	for (int i = 0; i < vector_size; i++) {
		my_string_result = vector_at(hVector, i);
		char * c_str = my_string_c_str(my_string_result);
		printf("%s\t", c_str);
	}
	fclose(fp);
	return hVector;
}

return 0;
*/

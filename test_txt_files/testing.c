#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "vector.h"
#include "assoc_arr.h"

// const DASH is treated as a 'wildcard' character
// a wildcard is any character that has not been guess yet
const char DASH = '-';

int word_length_input(void);
int num_guesses_input(void);
void read_words_from_dict(GEN_VECTOR hVector, int length);

//Precondition:current_word_family, new_key and word are all handles to valid
// MY_STRING opaque objects. guess is an alphabetical character that can be either
// upper or lower case.
//Postcondition: Returns SUCCESS after replacing the string in new_key with the key
// value formed by considering the current word family, the word and the guess.
// Returns failure in the case of a resizing problem with the new_key string.
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);


int main(int argc, char* argv[]) {

	int word_length;
	int num_guesses;
	int vector_size;
	MY_STRING hCurrent_WF_key;
	GEN_VECTOR hVector_word_bank;

	FILE *fp = fopen("./dictionary.txt", "r");

	//word_length = word_length_input();
	word_length = 2;
	hVector_word_bank = gen_vector_init_default(my_string_assignment, my_string_destroy);
	// read words of 'word_length' in hVector_words
	read_words_from_dict(hVector_word_bank, word_length);
	
	// handle exception when no words of given length exist
	vector_size = gen_vector_get_size(hVector_word_bank);
	while (vector_size == 0) {
		printf("No words of length %d exist, choose another length between 1 and 29.\n", vector_size);
		gen_vector_destroy(&hVector_word_bank);
		word_length = word_length_input();
		hVector_word_bank = gen_vector_init_default(my_string_assignment, my_string_destroy);
		vector_size = gen_vector_get_size(hVector_word_bank);
	}

	// init the current WF key to all dashes, which are treated as wildcards
	hCurrent_WF_key = my_string_init_default();
	for (int i = 0; i < word_length; i++) {
		my_string_push_back(hCurrent_WF_key, DASH);
	}

	//num_guesses = num_guesses_input();
	num_guesses = 20;
	printf("\nSTART GAME!\n\n");
	
	while (num_guesses != 0) {
		printf("You have %d guesses left.\n", num_guesses);

		char guess = 'a';

		NODE_MY_STR* list_head = NULL;

		// iterate through each my_string that's in the current word bank
		for (int i = 0; i < gen_vector_get_size(hVector_word_bank); i++) {
			MY_STRING current_word = gen_vector_at(hVector_word_bank, i);
			MY_STRING tempKey = my_string_init_default();
			// determine a word's W/F key. I signifies the character number
			for (int j = 0; j < word_length; j++) {
				char char_in_current_key = *my_string_at(hCurrent_WF_key, j);
				// when a char in the current key is not a dash, the user has successfully 
				// guessed this character before. So, make sure it's in the new key.
				if (char_in_current_key != DASH) {
					my_string_push_back(tempKey, char_in_current_key);
				}
				else if (char_in_current_key == guess) {
					my_string_push_back(tempKey, guess);
				}
				else {
					my_string_push_back(tempKey, DASH);
				}
			}
			// if a node with a key == tempKey exists, add the current my_string to the 
			// respective generic vector held within that node. If necessary, create a 
			// new node that has a key = tempKey and push current my_string, 
			linked_list_push_back(list_head, tempKey, current_word);
			my_string_destroy(&tempKey);
		}
		// iterate over the linked list and assign the current WF key and current WF
		// vector's values
		linked_list_assign_new_wf(list_head, hCurrent_WF_key, hVector_word_bank);

		printf("\n\n");
		num_guesses--;
	}




	gen_vector_destroy(&hVector_word_bank);
	return 0;
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

void read_words_from_dict(GEN_VECTOR hVector, int length) {
	MY_STRING hMy_string = NULL;
	hMy_string = my_string_init_default();

	FILE *fp = fopen("./dictionary.txt", "r");

	printf("...finding all strings in dict where str size == %d\n", length);
	while (my_string_extraction(hMy_string, fp))
	{
		if (my_string_get_size(hMy_string) == length) {
			gen_vector_push_back(hVector, hMy_string);
		}
	}
	my_string_destroy(&hMy_string);

	int vector_size = gen_vector_get_size(hVector);
	
	MY_STRING my_string_result = NULL;
	for (int i = 0; i < vector_size; i++) {
		my_string_result = gen_vector_at(hVector, i);
		char * c_str = my_string_c_str(my_string_result);
		printf("%s\t", c_str);
	}
	printf("\n");
	fclose(fp);
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess) {

}


/*
// LAB 7 part 1, WORKS NO MEM LEAKS!!!
int main(int argc, char *argv[]) {
	VECTOR* vector_array[29] = { NULL };

	MY_STRING hMy_string = NULL;
	hMy_string = my_string_init_default();

	FILE* fp;
	fp = fopen("./dictionary.txt", "r");


	for (int i = 0; i < 29; i++) {
		VECTOR hVector = NULL;
		hVector = vector_init_default();
		vector_array[i] = hVector;
	}

	while (my_string_extraction(hMy_string, fp))
	{
		int string_size = my_string_get_size(hMy_string);
		vector_push_back(vector_array[string_size - 1], hMy_string);
	}

	my_string_destroy(&hMy_string);
	fclose(fp);

	for (int i = 0; i < 29; i++) {
		int vector_size;

		vector_size = vector_get_size(vector_array[i]);

		printf("%d words with %d characters in them\n", vector_size, i + 1);
	}
	for (int i = 0; i < 29; i++) {
		VECTOR *v = &(vector_array[i]);
		vector_destroy(v);
	}

	return 0;
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
GAME!!!!
GAME!!!!
GAME!!!!
GAME!!!!
GAME!!!!

GAME!!!!


return 0;
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "vector.h"

// const DASH is treated as a 'wildcard' character
// a wildcard is any character that has not been guess yet
const char DASH = '-';

int word_length_input(void);
int num_guesses_input(void);
char guess_char_input(void);
void read_words_from_dict(GEN_VECTOR hVector, int length);

int main(int argc, char* argv[]) {

	int word_length;
	int num_guesses;
	int vector_size;
	MY_STRING hCurrent_WF_key;
	GEN_VECTOR hVector_word_bank;

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

	num_guesses = num_guesses_input();

	printf("\nSTART GAME!\n\n");

	while (num_guesses != 0) {
		printf("You have %d guesses left.\n", num_guesses);

		char guess = guess_char_input();

		GEN_VECTOR wf_words = gen_vector_init_default(gen_vector_assignment, gen_vector_destroy);
		GEN_VECTOR wf_keys = gen_vector_init_default(my_string_assignment, my_string_destroy);

		// iterate through each my_string that's in the current word bank
		for (int i = 0; i < gen_vector_get_size(hVector_word_bank); i++) {
			MY_STRING current_word = gen_vector_at(hVector_word_bank, i);
			MY_STRING temp_key = my_string_init_default();
			GEN_VECTOR temp_vector = gen_vector_init_default(my_string_assignment, my_string_destroy);
			// determine a word's W/F key. I signifies the character number
			for (int j = 0; j < word_length; j++) {
				char char_in_current_key = *my_string_at(hCurrent_WF_key, j);
				char char_in_current_word = *my_string_at(current_word, j);
				// when a char in the current key is not a dash, the user has successfully
				// guessed this character before. So, make sure it's in the new key.
				if (char_in_current_key != DASH) {
					my_string_push_back(temp_key, char_in_current_key);
				}
				else if (char_in_current_word == guess) {
					my_string_push_back(temp_key, guess);
				}
				else {
					my_string_push_back(temp_key, DASH);
				}
			}
			printf("iter: %d num WF's: %d\nCurrent WF: %s\n\n", i, gen_vector_get_size(wf_words), my_string_c_str(temp_key));
			// if there's a match between the current word's key and a key
			// existing in wf_keys, append the corresponsing vector in wf_words
			int match_exists = FALSE;
			for (int j = 0; j < gen_vector_get_size(wf_keys); j++) {
				if (my_string_compare(temp_key, gen_vector_at(wf_keys, j)) == 0) {
					match_exists = TRUE;
					GEN_VECTOR double_temp = gen_vector_at(wf_words, j);
					gen_vector_push_back(double_temp, current_word);

				}
			}
			// if there's no match, add a key / value entry into the gen_vectors
			if (match_exists == FALSE) {
				// push a new key onto the keys
				gen_vector_push_back(wf_keys, temp_key);
				// allocate memory for a new vector and push the current word into it
				gen_vector_push_back(temp_vector, current_word);
				// push the temp vector for the WF into the vectors gen vector
				gen_vector_push_back(wf_words, temp_vector);

			}
			gen_vector_destroy(&temp_vector);
			my_string_destroy(&temp_key);
			my_string_destroy(&current_word);
		}
		int num_wfs = gen_vector_get_size(wf_words);

		int sum_wfs = 0;
		for (int i = 0; i < num_wfs; i++) {
			char *wf_c_str = my_string_c_str(gen_vector_at(wf_keys, i));
			int num_members = gen_vector_get_size(gen_vector_at(wf_words, i));
			sum_wfs += num_members;
			printf("Word family %s has %d members. Total so far: %d\n", wf_c_str, num_members, sum_wfs);
		}
		printf("selecting wf with largest popuilation:");

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

char guess_char_input(void) {
	int numOfConversions;
	char input;
	printf("Guess a character by entering a character a-z: ");

	numOfConversions = scanf("%c", &input);

	if (input < 97 ) {
		input += 32;
	}

	while (numOfConversions == 0 || input < 97 || input > 122)
	{
		char ch;
		scanf("%c", &ch);
		while (ch != '\n') {
			scanf("%c", &ch);
		}

		printf("Guess a character by entering a character a-z: ");
		numOfConversions = scanf("%c", &input);

		if (input < 97 ) {
			input += 32;
		}
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

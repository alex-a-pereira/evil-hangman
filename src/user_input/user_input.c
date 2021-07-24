#include "user_input.h"

/*
 * HELPER FUNCS - private to this module
*/

void clear_buffer(void) {
	char ch;
	scanf("%c", &ch);
	while (ch != '\n')
		scanf("%c", &ch);
}

Boolean validate_not_already_guessed (char current_guess, MY_STRING previous_guesses) {
	for (int i = 0; i < my_string_get_size(previous_guesses); i++) {
		char prev_guess = *my_string_at(previous_guesses, i);
		if (current_guess == prev_guess) {
			return TRUE;
		}
	}

	return FALSE;
}

/*
 * EXPOSED API
*/

int get_num_guesses_input(void) {
  int input, numOfConversions;
	printf("How many guesses would you like to have? Enter a positive integer: ");
	numOfConversions = scanf("%d", &input);

	while (numOfConversions == 0 || input < 1)
	{
		clear_buffer();

		printf("I'm sorry, please enter an integer greater than 1: ");
		numOfConversions = scanf("%d", &input);
	}

	clear_buffer();
	return input;
}

int get_word_length_input(void) {
  int input, numOfConversions;
	printf("What length word do you want to play with? Enter an integer between 1 and 29: ");
	numOfConversions = scanf("%d", &input);

	while (numOfConversions == 0 || input < 1 || input > 29)
	{
		clear_buffer();
		printf("I'm sorry, please enter an integer between 0 and 29: ");
		numOfConversions = scanf("%d", &input);
	}
	clear_buffer();
	return input;
}

char get_char_guess_input(MY_STRING previous_guesses) {
  int numOfConversions;
	char input;
	
	printf("Guess a character by entering a character a-z: ");
	numOfConversions = scanf("%c", &input);
	Boolean already_guessed = validate_not_already_guessed(input, previous_guesses);


	while (numOfConversions == 0 || input < 97 || input > 122 || already_guessed == TRUE)
	{
		if (already_guessed == TRUE) {
			printf("You've already guessed %c. ", input);
		}
		
		clear_buffer();
		
		printf("Guess a letter by entering a character a-z: ");
		numOfConversions = scanf("%c", &input);
		
		already_guessed = validate_not_already_guessed(input, previous_guesses);
	}
	clear_buffer();
	return input;
}
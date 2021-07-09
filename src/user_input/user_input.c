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

int get_char_guess_input(void) {
  return 0;
}
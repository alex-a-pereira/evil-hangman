// Linked list w/ key/value pairs courtesy of Jim Lawless
// https://lawlessguy.wordpress.com/2016/02/11/a-simple-associative-array-library-in-c/
#include <stdlib.h>
#include <stdio.h>

// Data types
#include "data_types/my_string/my_string.h"
#include "data_types/vector/vector.h"
#include "data_types/word_linked_list/word_linked_list.h"

// utils
#include "user_input/user_input.h"

// Status messages
#include "ui/game_print.h"

const char DASH = '-'; // const DASH is treated as a 'wildcard' char

char guess_char_input(MY_STRING previous_guesses);
void read_words_from_dict(G_VECTOR hVector, int length);

struct GameState {
	int word_length;
	int num_guesses;
	MY_STRING hGuessed_letters;
	MY_STRING hCurrent_WF_key;
	G_VECTOR hVector_word_bank;
	Boolean victory;
};


struct GameState game_state;

void init_game_state(void) {
	game_state.word_length = get_word_length_input();
	game_state.hVector_word_bank = g_vector_init_default(my_string_assignment, my_string_destroy);
	game_state.victory = FALSE;
	game_state.num_guesses = get_num_guesses_input();
	game_state.hGuessed_letters = my_string_init_default();
	read_words_from_dict(game_state.hVector_word_bank, game_state.word_length);
}

// gets word size input from user and initializes game_state word band and word_length
void collect_word_size_input_and_init_word_bank(void) {
	// TODO: should be able to hardcode to 0 initially, call this from init_game_state
	int num_words_of_specified_length = g_vector_get_size(game_state.hVector_word_bank);
	while (num_words_of_specified_length == 0) {
		printf("No words of length %d exist. ", game_state.word_length);
		g_vector_destroy(&game_state.hVector_word_bank);
		game_state.word_length = get_word_length_input();
		game_state.hVector_word_bank = g_vector_init_default(my_string_assignment, my_string_destroy);
		read_words_from_dict(game_state.hVector_word_bank, game_state.word_length);
		num_words_of_specified_length = g_vector_get_size(game_state.hVector_word_bank);
	}
}


int main(int argc, char* argv[]) {
	print_welcome();

	init_game_state();
	collect_word_size_input_and_init_word_bank();

	// init the current WF key to all dashes, which are treated as wildcards
	game_state.hCurrent_WF_key = my_string_init_default();
	for (int i = 0; i < game_state.word_length; i++) {
		my_string_push_back(game_state.hCurrent_WF_key, DASH);
	}

	print_begin();

	while (game_state.num_guesses != 0) {
		int words_remaining = g_vector_get_size(game_state.hVector_word_bank);
		if (words_remaining == 1 && my_string_contains(game_state.hCurrent_WF_key, DASH) == FALSE) {
			MY_STRING winning_word = NULL;
			my_string_assignment(&winning_word, g_vector_at(game_state.hVector_word_bank, 0));
			printf("You correctly guessed the word: %s\n", my_string_c_str(winning_word));
			my_string_destroy(&winning_word);
			
			game_state.victory = TRUE;
			break;
		}

		printf("\n------------------------------------\n");
		if (game_state.num_guesses == 1) {
			printf("You have 1 guess left.\n");
		}
		else {
			printf("You have %d guesses left.\n", game_state.num_guesses);
		}
		printf("Number of words remaining: %d\n", words_remaining);
		
		printf("Used letters: ");
		for (int i = 0; i < my_string_get_size(game_state.hGuessed_letters); i++) {
			printf("%c ", *my_string_at(game_state.hGuessed_letters, i));
		}
		printf("\n");
		printf("Word: %s\n", my_string_c_str(game_state.hCurrent_WF_key));
		printf("------------------------------------\n\n");

		char guess = guess_char_input(game_state.hGuessed_letters);
		my_string_push_back(game_state.hGuessed_letters, guess);
		
		
		Node* linked_list_head = NULL;

		// iterate through each my_string that's in the current word bank
		for (int i = 0; i < g_vector_get_size(game_state.hVector_word_bank); i++) {
			MY_STRING current_word = g_vector_at(game_state.hVector_word_bank, i);
			MY_STRING temp_key = my_string_init_default();
			// determine a word's W/F key. I signifies the character number
			for (int j = 0; j < game_state.word_length; j++) {
				char char_in_current_key = *my_string_at(game_state.hCurrent_WF_key, j);
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
			linked_list_insert_word(&linked_list_head, temp_key, current_word);

			my_string_destroy(&temp_key);
			my_string_destroy(&current_word);
		}

		linked_list_print(linked_list_head);
		Boolean correct = linked_list_assign_new_wf(linked_list_head, game_state.hVector_word_bank, game_state.hCurrent_WF_key);
		
		if (correct != TRUE) {
			printf("\nThere were no %c's in the word!\n", guess);
			game_state.num_guesses--;
		}
		else {
			printf("\n%c was in the word!\n", guess);
		}
		linked_list_destroy(&linked_list_head);
	}
	
	g_vector_destroy(&game_state.hVector_word_bank);
	my_string_destroy(&game_state.hGuessed_letters);
	my_string_destroy(&game_state.hCurrent_WF_key);

	if (game_state.victory == TRUE) {
		print_winner();
	}
	else {
		print_loser();
	}

	return 0;
}

void _clear_buffer(void) {
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

char guess_char_input(MY_STRING previous_guesses) {
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
		
		_clear_buffer();
		
		printf("Guess a letter by entering a character a-z: ");
		numOfConversions = scanf("%c", &input);
		
		already_guessed = validate_not_already_guessed(input, previous_guesses);
	}
	_clear_buffer();
	return input;
}

void read_words_from_dict(G_VECTOR hVector, int length) {
	MY_STRING hMy_string = NULL;
	hMy_string = my_string_init_default();

	FILE *fp = fopen("./src/dictionary.txt", "r");

	printf("Loading words of size %d...\n", length);

	while (my_string_extraction(hMy_string, fp))
	{
		if (my_string_get_size(hMy_string) == length) {
			g_vector_push_back(hVector, hMy_string);
		}
	}
	my_string_destroy(&hMy_string);

	int vector_size = g_vector_get_size(hVector);

	fclose(fp);
}

// Linked list w/ key/value pairs courtesy of Jim Lawless
// https://lawlessguy.wordpress.com/2016/02/11/a-simple-associative-array-library-in-c/
#include <stdlib.h>
#include <stdio.h>

// Data types
#include "data_types/my_string/my_string.h"
#include "data_types/vector/vector.h"
#include "data_types/word_linked_list/word_linked_list.h"

// state
#include "game_state/game_state.h"

// utils
#include "user_input/user_input.h"
#include "dictionary/dictionary.h"

// Status messages
#include "ui/game_print.h"

const char DASH = '-'; // const DASH is treated as a 'wildcard' char

int main(int argc, char* argv[]) {
	print_welcome();

	init_game_state();
	collect_word_size_input_and_init_word_bank();

	struct GameState game_state = get_game_state();

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

		char guess = get_char_guess_input(game_state.hGuessed_letters);
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

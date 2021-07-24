#include "game_state.h"

struct GameState game_state;

struct GameState get_game_state(void) {
  return game_state;
}


void init_game_state(void) {
	game_state.word_length = get_word_length_input();
	game_state.hVector_word_bank = g_vector_init_default(my_string_assignment, my_string_destroy);
	game_state.victory = FALSE;
	game_state.num_guesses = get_num_guesses_input();
	game_state.previous_guesses = my_string_init_default();
	extract_correct_len_words_from_dict(game_state.hVector_word_bank, game_state.word_length);
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
		extract_correct_len_words_from_dict(game_state.hVector_word_bank, game_state.word_length);
		num_words_of_specified_length = g_vector_get_size(game_state.hVector_word_bank);
	}
}

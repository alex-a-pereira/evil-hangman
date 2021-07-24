#include "../data_types/my_string/my_string.h"
#include "../data_types/vector/vector.h"

// TODO: these don't need to be here
// once we have proper setters we can remove them
#include "../user_input/user_input.h"
#include "../dictionary/dictionary.h"

struct GameState {
	// are set by user inputs
	int word_length;
	int num_guesses;
	// my_string object containing all guessed letters
	MY_STRING previous_guesses;
	MY_STRING hCurrent_WF_key;
	// contains all the remaining possible words (not containing any of the previous guesses)
	G_VECTOR hVector_word_bank;
	// is set to true when we determine user has won - used to determine if loop should break
	Boolean victory;
};

void init_game_state(void);
void collect_word_size_input_and_init_word_bank(void);

struct GameState get_game_state(void);
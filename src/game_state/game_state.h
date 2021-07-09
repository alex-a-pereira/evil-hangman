#include "../data_types/my_string/my_string.h"
#include "../data_types/vector/vector.h"

// TODO: these don't need to be here
// once we have proper setters we can remove them
#include "../user_input/user_input.h"
#include "../dictionary/dictionary.h"

struct GameState {
	int word_length;
	int num_guesses;
	MY_STRING hGuessed_letters;
	MY_STRING hCurrent_WF_key;
	G_VECTOR hVector_word_bank;
	Boolean victory;
};

void init_game_state(void);
void collect_word_size_input_and_init_word_bank(void);

struct GameState get_game_state(void);
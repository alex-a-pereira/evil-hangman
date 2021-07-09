#include "dictionary.h"

// pushes every word from dictionary file that is desired_length chars long onto the back of the vector 
void extract_correct_len_words_from_dict(G_VECTOR hVector, int desired_length) {
	MY_STRING h_temp_string = NULL;
	h_temp_string = my_string_init_default();
	FILE *fp = fopen("./src/dictionary/dictionary.txt", "r");

	printf("Loading words of size %d...\n", desired_length);

	// extract each word individually ("individual" determined by EOL whitespace char)
	while (my_string_extraction(h_temp_string, fp))
	{
		// if current word in dict is correct length, push it onto vector
		if (my_string_get_size(h_temp_string) == desired_length) {
			g_vector_push_back(hVector, h_temp_string);
		}
	}
	my_string_destroy(&h_temp_string);

	fclose(fp);
}
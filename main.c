// Linked list w/ key/value pairs courtesy of Jim Lawless
// https://lawlessguy.wordpress.com/2016/02/11/a-simple-associative-array-library-in-c/
#include <stdlib.h>
#include <crtdbg.h>  
#include <stdio.h>
#include "my_string.h"
#include "vector.h"
#include "game_print.h"

typedef struct node Node;
struct node {
	MY_STRING key;
	G_VECTOR data;
	Node* next;
};

Status linked_list_insert_word(Node** pHead, MY_STRING key_name, MY_STRING current);
void linked_list_destroy(Node** pHead);
Node* node_init_default();
void linked_list_print(Node* head);
Boolean linked_list_assign_new_wf(Node* head, G_VECTOR current_wf, MY_STRING current_key);

const char DASH = '-'; // const DASH is treated as a 'wildcard' char

int word_length_input(void);
int num_guesses_input(void);
char guess_char_input(MY_STRING previous_guesses);
void read_words_from_dict(G_VECTOR hVector, int length);

int main(int argc, char* argv[]) {
	print_welcome();
	int word_length, num_guesses, vector_size;
	MY_STRING hGuessed_letters = my_string_init_default();
	MY_STRING hCurrent_WF_key;
	G_VECTOR hVector_word_bank;
	Boolean victory = FALSE;

	word_length = 8; //word_length_input();
	hVector_word_bank = g_vector_init_default(my_string_assignment, my_string_destroy);
	read_words_from_dict(hVector_word_bank, word_length);

	// no words of given length exist
	vector_size = g_vector_get_size(hVector_word_bank);
	while (vector_size == 0) {
		printf("No words of length %d exist. ", word_length);
		g_vector_destroy(&hVector_word_bank);
		word_length = word_length_input();
		hVector_word_bank = g_vector_init_default(my_string_assignment, my_string_destroy);
		read_words_from_dict(hVector_word_bank, word_length);
		vector_size = g_vector_get_size(hVector_word_bank);
	}
	// init the current WF key to all dashes, which are treated as wildcards
	hCurrent_WF_key = my_string_init_default();
	for (int i = 0; i < word_length; i++) {
		my_string_push_back(hCurrent_WF_key, DASH);
	}
	print_begin();
	num_guesses = 6; // num_guesses_input();
	while (num_guesses != 0) {
		int words_remaining = g_vector_get_size(hVector_word_bank);
		if (words_remaining == 0) {
			victory = TRUE;
			break;
		}

		printf("\n------------------------------------\n");
		if (num_guesses == 1) {
			printf("You have 1 guess left.\n");
		}
		else {
			printf("You have %d guesses left.\n", num_guesses);
		}
		printf("Number of words remaining: %d\n", words_remaining);
		
		printf("Used letters: ");
		for (int i = 0; i < my_string_get_size(hGuessed_letters); i++) {
			printf("%c ", *my_string_at(hGuessed_letters, i));
		}
		printf("\n");
		printf("Word: %s\n", my_string_c_str(hCurrent_WF_key));
		printf("------------------------------------\n\n");

		char guess = guess_char_input(hGuessed_letters);
		my_string_push_back(hGuessed_letters, guess);
		
		
		Node* linked_list_head = NULL;

		// iterate through each my_string that's in the current word bank
		for (int i = 0; i < g_vector_get_size(hVector_word_bank); i++) {
			MY_STRING current_word = g_vector_at(hVector_word_bank, i);
			MY_STRING temp_key = my_string_init_default();
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
			linked_list_insert_word(&linked_list_head, temp_key, current_word);

			my_string_destroy(&temp_key);
			my_string_destroy(&current_word);
		}

		linked_list_print(linked_list_head);
		Boolean correct = linked_list_assign_new_wf(linked_list_head, hVector_word_bank, hCurrent_WF_key);
		
		if (correct != TRUE) {
			printf("\nThere were no %c's in the word!\n", guess);
			num_guesses--;
		}
		else {
			printf("\n%c was in the word!\n", guess);
		}
		linked_list_destroy(&linked_list_head);
	}
	
	g_vector_destroy(&hVector_word_bank);
	my_string_destroy(&hGuessed_letters);
	my_string_destroy(&hCurrent_WF_key);

	if (victory == TRUE) {
		print_winner();
	}
	else {
		print_loser();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

Node* node_init_default() {
	Node* pNode = NULL;
	pNode = (Node*)malloc(sizeof(Node));

	if (pNode != NULL) {
		pNode->data = g_vector_init_default(my_string_assignment, my_string_destroy);
		pNode->key = my_string_init_default();
		pNode->next = NULL;
	}
	return pNode;
}

Status linked_list_insert_word(Node** pHead, MY_STRING key_name, MY_STRING current) {

	Node* temp = NULL;

	if (*pHead == NULL) { // if no nodes in list, insert a head
		temp = node_init_default();
		my_string_assignment(&temp->key, key_name);
		g_vector_push_back(temp->data, current);

		*pHead = temp;
		return SUCCESS;
	}
		for (temp = *pHead; ; temp = temp->next) { // iterate thru nodes
			if (my_string_compare(key_name, temp->key) == 0) { // node's key matches cur_words key
				g_vector_push_back(temp->data, current);
				return SUCCESS;
			}
			if (temp->next == NULL) { // reached end of list
				Node* double_temp = temp->next;
				double_temp = node_init_default();

				my_string_assignment(&(double_temp->key), key_name);
				g_vector_push_back(double_temp->data, current);
				
				temp->next = double_temp;
				
				return SUCCESS;
			}
	}
	return FAILURE;
}

void linked_list_print(Node* head) {
	while (head != NULL) {
		int size = g_vector_get_size(head->data);
		char * temp_key = my_string_c_str(head->key);
		printf("Key: %s, num words: %d \n", temp_key, size);
		head = head->next;
	}
}

Boolean linked_list_assign_new_wf(Node* head, G_VECTOR current_wf, MY_STRING current_key) {
	Boolean correct_guess = FALSE;
	
	int max_idx = 0;
	int max_size = 0;

	Node *temp = head;

	int i = 0;
	while (temp != NULL) {
		int current_size = g_vector_get_size(temp->data);
		if (current_size > max_size) {
			max_idx = i;
			max_size = current_size;
		}
		i++;
		temp = temp->next;
	}

	temp = head;
	i = 0;
	while (i < max_idx) {
		temp = temp->next;
		i++;
	}
	int cur_sz = g_vector_get_size(temp->data);
	printf("Key with most words: '%s' size %d\n", my_string_c_str(temp->key), cur_sz);
	g_vector_assignment(&current_wf, temp->data);
	
	if (my_string_compare(current_key, temp->key) != 0) {
		correct_guess = TRUE;
	}
	my_string_assignment(&current_key, temp->key);	

	return correct_guess;
}

void linked_list_destroy(Node** pHead) {
	Node* temp;
	temp = *pHead;
	while (temp != NULL) {
		*pHead = temp->next;
		g_vector_destroy(&temp->data);
		my_string_destroy(&temp->key);
		free(temp);
		temp = *pHead;
	}
	*pHead = NULL;
}


void clear_buffer(void) {
	char ch;
	scanf("%c", &ch);
	while (ch != '\n')
		scanf("%c", &ch);
}

int word_length_input(void)
{
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

int num_guesses_input(void) {
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

char guess_char_input(MY_STRING previous_guesses) {
	int numOfConversions;
	char input;
	
	printf("Guess a character by entering a character a-z: ");
	numOfConversions = scanf("%c", &input);
	Boolean already_guessed = FALSE;


	for (int i = 0; i < my_string_get_size(previous_guesses); i++) {
		char prev_guess = *my_string_at(previous_guesses, i);
		if (input == prev_guess) {
			already_guessed = TRUE;
		}
	}

	while (numOfConversions == 0 || input < 97 || input > 122 || already_guessed == TRUE)
	{
		if (already_guessed == TRUE) {
			printf("You've already guessed %c. ", input);
		}
		
		clear_buffer();
		
		printf("Guess a letter by entering a character a-z: ");
		numOfConversions = scanf("%c", &input);
		
		already_guessed = FALSE;
		for (int i = 0; i < my_string_get_size(previous_guesses); i++) {
			char prev_guess = *my_string_at(previous_guesses, i);
			if (input == prev_guess) {
				already_guessed = TRUE;
			}
		}
	}
	clear_buffer();
	return input;
}

void read_words_from_dict(G_VECTOR hVector, int length) {
	MY_STRING hMy_string = NULL;
	hMy_string = my_string_init_default();

	FILE *fp = fopen("./dictionary.txt", "r");

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

#include "word_linked_list.h"

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

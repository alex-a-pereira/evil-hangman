#include <stdio.h>
#include <stdlib.h>
#include "assoc_arr.h"

typedef struct node_my_str Node_my_str;
struct node_my_str
{
	MY_STRING *key;
	GEN_VECTOR data; // gen vector of My_string objects
	Node_my_str *next;
};

NODE_MY_STR node_my_str_init_default(void)
{
	Node_my_str *pNode_my_str = NULL;
	pNode_my_str = (Node_my_str *)malloc(sizeof(Node_my_str));
	pNode_my_str->key = my_string_init_default();
	pNode_my_str->data = gen_vector_init_default(my_string_assignment, my_string_destroy);
	pNode_my_str->next = NULL;
	return pNode_my_str;
}

Status node_my_str_push_back(NODE_MY_STR hNode, MY_STRING hString_to_push) {
	Node_my_str *pNode = (Node_my_str*)hNode;
	gen_vector_push_back(pNode->data, hString_to_push);
	return SUCCESS;
}

void linked_list_destroy(NODE_MY_STR* phNode) {
	Node_my_str *pNode = (Node_my_str*)*phNode;

	Node_my_str *tempNode = (Node_my_str *)malloc(sizeof(Node_my_str));

	while (pNode->next != NULL) {
		tempNode = pNode->next;

		gen_vector_destroy(pNode->data);
		free(pNode->data);
		free(pNode);

		pNode = tempNode;
	}
	free(tempNode);
	*phNode = NULL;
}

Status linked_list_push_back(NODE_MY_STR head, MY_STRING key, MY_STRING current_word) {
	Node_my_str *tempNode = (Node_my_str *)malloc(sizeof(Node_my_str));

	if (head == NULL) {
		head = node_my_str_init_default();
		Node_my_str *pHead = (Node_my_str*)head;
		my_string_assignment(pHead->key, key);

		gen_vector_push_back(pHead->data, current_word);


		return SUCCESS;
	}

	Node_my_str *pHead = (Node_my_str*)head;
	tempNode = pHead;

	while (tempNode->next != NULL) {
		if (my_string_compare(key, tempNode->key) == 0) {
			gen_vector_push_back(tempNode->data, current_word);
			return SUCCESS;
		}
		else {
			tempNode = tempNode->next;
		}
	}

	tempNode->next = node_my_str_init_default();
	my_string_assignment(tempNode->next->key, key);
	gen_vector_push_back(tempNode->next->data, current_word);

	free(tempNode);
	return FAILURE;
}

Status linked_list_assign_new_wf(NODE_MY_STR head, MY_STRING hKey, GEN_VECTOR hWord_bank) {
	Node_my_str *pHead = (Node_my_str *)head;
	Node_my_str *tempNode = (Node_my_str *)malloc(sizeof(Node_my_str));

	MY_STRING hMax_key = my_string_init_default();
	int max_size = 0;

	if (pHead->next == NULL) {
		my_string_assignment(hMax_key, pHead->key);
	}

	tempNode = pHead;
	while (tempNode != NULL) {
		int node_size = gen_vector_get_size(tempNode->data);

		if (node_size > max_size) {
			my_string_assignment(hMax_key, tempNode->key);
		}
		tempNode = tempNode->next;
	}
	my_string_assignment(hKey, hMax_key);

	// reset tempNode to head in order to iterate from the start of the list to the node
	// with a key == max_key
	tempNode = pHead;
	while (my_string_compare(tempNode->key, hMax_key) != 0) {
		tempNode = tempNode->next;
	}
	while (gen_vector_get_size(hWord_bank) > 0) {
		gen_vector_pop_back(hWord_bank);
	}

	for (int i = 0; i < gen_vector_get_size(tempNode->data); i++) {
		gen_vector_push_back(hWord_bank, gen_vector_at(tempNode->data, i));
	}

	free(tempNode);
}


/*

Status node_my_str_set(NODE_MY_STR hNode_my_str, MY_STRING key, GEN_VECTOR data)
{
	Node_my_str *pNode_my_str = (Node_my_str *)hNode_my_str;

	if (pNode_my_str->key == NULL)
	{
		pNode_my_str->key = my_string_init_default();
		my_string_assignment(pNode_my_str->key, key);

		for (int i = 0; i < gen_vector_get_size(data); i++) {
			MY_STRING string_in_data = gen_vector_at(data, i);
			gen_vector_push_back(pNode_my_str->data, string_in_data);
		}
		pNode_my_str->next = NULL;
		return;
	}
	else {
		Node_my_str temp_node =
	}
	for (map = m;; map = map->nxt)
	{
		if (!strcasecmp(name, map->name))
		{
			if (map->value != NULL)
			{
				map->value = value;
				return;
			}
		}
		if (map->nxt == NULL)
		{
			map->nxt = (struct map_t *) malloc(sizeof(struct map_t));
			map = map->nxt;
			map->name = (char *)malloc(strlen(name) + 1);
			strcpy(map->name, name);
			map->value = value;
			map->nxt = NULL;
			return;
		}
	}
}

int map_get(struct map_t *m, char *name)
{
	struct map_t *map;
	for (map = m; map != NULL; map = map->nxt)
	{
		if (!strcasecmp(name, map->name))
		{
			return map->value;
		}
	}
	return -99;
}

void map_destroy(struct map_t *m)
{
	struct map_t *temp;
	while (m != NULL)
	{
		temp = m->nxt;
		printf("Deleting node w/ key: %s\n", m->name);
		free(m->name);
		free(m);
		m = temp;
	}
}
*/
#include "node.h"

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

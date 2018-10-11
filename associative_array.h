#ifndef ASSOC_ARR_H
#define ASSOC_ARR_H

typedef struct node Node;
struct node {
	int data;
	int height;
	Node* left;
	Node* right;
};

typedef void* ASSOC_ARR;

void node_destory(Node* t);
Node* assoc_arr_find(int e, Node *t);
Node* assoc_arr_find_min(Node *t);
Node* assoc_arr_find_max(Node *t);
Node* assoc_arr_insert(int data, Node *t);
Node* assoc_arr_delete(int data, Node *t);
int get(Node* n);

#endif
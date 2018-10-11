// SOURCE: https://www.youtube.com/watch?v=FNeL18KsWPc
// SOURCE: http://www.zentut.com/c-tutorial/c-avl-tree/
// SOURCE: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
// SOURCE: https://www.geeksforgeeks.org/avl-tree-set-2-deletion/

#include <stdio.h>
#include "associative_array.h"

void node_destory(Node* t)
{
	if (t != NULL)
	{
		dispose(t->left);
		dispose(t->right);
		free(t);
	}
}


Node* find(int e, Node* t)
{
	if (t == NULL)
		return NULL;
	if (e < t->data)
		return find(e, t->left);
	else if (e > t->data)
		return find(e, t->right);
	else
		return t;
}

/*
find minimum Node's key
*/
Node* find_min(Node* t)
{
	if (t == NULL)
		return NULL;
	else if (t->left == NULL)
		return t;
	else
		return find_min(t->left);
}

/*
find maximum Node's key
*/
Node* find_max(Node* t)
{
	if (t != NULL)
		while (t->right != NULL)
			t = t->right;

	return t;
}

/*
get the height of a Node
*/
static int height(Node* n)
{
	if (n == NULL)
		return -1;
	else
		return n->height;
}

/*
get maximum value of two integers
*/
static int max(int l, int r)
{
	return l > r ? l : r;
}

/*
perform a rotation between a k2 Node and its left child

note: call single_rotate_with_left only if k2 Node has a left child
*/

static Node* single_rotate_with_left(Node* k2)
{
	Node* k1 = NULL;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	return k1; /* new root */
}

/*
perform a rotation between a Node (k1) and its right child

note: call single_rotate_with_right only if
the k1 Node has a right child
*/

static Node* single_rotate_with_right(Node* k1)
{
	Node* k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;

	return k2;  /* New root */
}

/*

perform the left-right double rotation,

note: call double_rotate_with_left only if k3 Node has
a left child and k3's left child has a right child
*/

static Node* double_rotate_with_left(Node* k3)
{
	/* Rotate between k1 and k2 */
	k3->left = single_rotate_with_right(k3->left);

	/* Rotate between K3 and k2 */
	return single_rotate_with_left(k3);
}

/*
perform the right-left double rotation

notes: call double_rotate_with_right only if k1 has a
right child and k1's right child has a left child
*/



static Node* double_rotate_with_right(Node* k1)
{
	/* rotate between K3 and k2 */
	k1->right = single_rotate_with_left(k1->right);

	/* rotate between k1 and k2 */
	return single_rotate_with_right(k1);
}

/*
insert a new Node into the tree
*/
Node* insert(int e, Node* t)
{
	if (t == NULL)
	{
		/* Create and return a one-Node tree */
		t = (Node*)malloc(sizeof(Node));
		if (t == NULL)
		{
			fprintf(stderr, "Out of memory!!! (insert)\n");
			exit(1);
		}
		else
		{
			t->data = e;
			t->height = 0;
			t->left = t->right = NULL;
		}
	}
	else if (e < t->data)
	{
		t->left = insert(e, t->left);
		if (height(t->left) - height(t->right) == 2)
			if (e < t->left->data)
				t = single_rotate_with_left(t);
			else
				t = double_rotate_with_left(t);
	}
	else if (e > t->data)
	{
		t->right = insert(e, t->right);
		if (height(t->right) - height(t->left) == 2)
			if (e > t->right->data)
				t = single_rotate_with_right(t);
			else
				t = double_rotate_with_right(t);
	}
	/* Else X is in the tree already; we'll do nothing */

	t->height = max(height(t->left), height(t->right)) + 1;
	return t;
}

/*
remove a Node in the tree
*/
Node* delete(int e, Node* t)
{
	printf("Sorry; Delete is unimplemented; %d remains\n", e);
	return t;
}

/*
data data of a Node
*/
int get(Node* n)
{
	return n->data;
}

/*
Recursively display AVL tree or subtree
*/
void display_avl(Node* t)
{
	if (t == NULL)
		return;
	printf("%d", t->data);

	if (t->left != NULL)
		printf("(L:%d)", t->left->data);
	if (t->right != NULL)
		printf("(R:%d)", t->right->data);
	printf("\n");

	display_avl(t->left);
	display_avl(t->right);
}

#include "../my_string/my_string.h"
#include "../vector/vector.h"

typedef struct node Node;
struct node {
	MY_STRING key;
	G_VECTOR data;
	Node* next;
};

Node* node_init_default();

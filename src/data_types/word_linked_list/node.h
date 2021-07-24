#include "../my_string/my_string.h"
#include "../vector/vector.h"


/* EXAMPLES
	1. key = 'f---'
	vector data = ['fart', 'fear', 'fast']

	2.  key = '---f'
	vector data = ['half', 'calf']
*/

typedef struct node Node;
struct node {
	// key is a string matching the format for the vector data, e.g. '--f-'
	MY_STRING key;
	// vector is a vector containing words that match the format of the key, 
	G_VECTOR data;
	// you know what this does lol
	Node* next;
};

Node* node_init_default();

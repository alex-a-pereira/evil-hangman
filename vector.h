#ifndef VECTOR_H
#define VECTOR_H
#include "my_string.h"

typedef void* VECTOR;
//init
VECTOR vector_init_default(void);
//add item
Status vector_push_back(VECTOR hVector, Item hItem);
//remove item
Status vector_pop_back(VECTOR);
//check size and capacity
int vector_get_size(VECTOR);
int vector_get_capacity(VECTOR);
// see the particular item
MY_STRING vector_at(VECTOR hVector, int index);

//destroy
void vector_destroy(VECTOR*);
#endif
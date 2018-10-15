#ifndef VECTOR_H
#define VECTOR_H
#include "my_string.h"

typedef void* GEN_VECTOR;
//init
GEN_VECTOR gen_vector_init_default(Status(*item_assignment)(Item*, Item), void(*item_destroy)(Item*));
//add item
Status gen_vector_push_back(GEN_VECTOR hVector, Item hItem);
//remove item
Status gen_vector_pop_back(GEN_VECTOR);
//check size and capacity
int gen_vector_get_size(GEN_VECTOR);
int gen_vector_get_capacity(GEN_VECTOR);
// see the particular item
Item gen_vector_at(GEN_VECTOR hVector, int index);
Status gen_vector_push_back_data_at_idx(GEN_VECTOR hVector, Item hItem, int at_index);
Status gen_vector_assignment(Item* pLeft, Item Right);
void gen_vector_destroy(GEN_VECTOR*);
#endif
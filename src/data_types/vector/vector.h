#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

#include "../generic.h"
#include "../status.h"

typedef void* G_VECTOR;
G_VECTOR g_vector_init_default(Status(*item_assign)(Item_ptr, Item), void(*item_destroy)(Item_ptr));

Status g_vector_push_back(G_VECTOR hVector, Item item);

Status g_vector_pop_back(G_VECTOR hVector);

Item g_vector_at(G_VECTOR hVector, int index);

int g_vector_get_size(G_VECTOR hVector);

int g_vector_get_capacity(G_VECTOR hVector);

void g_vector_destroy(G_VECTOR* phVector);

Status g_vector_assignment(Item_ptr phLeft, Item hRight);

#endif
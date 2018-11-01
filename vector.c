#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

struct g_vector {
	int size;
	int capacity;
	Item_ptr data;
	Status(*item_assign)(Item_ptr, Item);
	void(*item_destroy)(Item_ptr);
};
typedef struct g_vector G_Vector;

G_VECTOR g_vector_init_default(Status(*item_assign)(Item_ptr, Item),
	void(*item_destroy)(Item_ptr)) {
	G_Vector* pVector;
	int i;
	pVector = (G_Vector*)malloc(sizeof(G_Vector));
	if (pVector != NULL) {
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->item_destroy = item_destroy;
		pVector->item_assign = item_assign;
		pVector->data = (Item_ptr)malloc(sizeof(Item)*pVector->capacity);
		if (pVector->data == NULL) {
			//object was not created
			free(pVector);
			pVector = NULL;
		}
		else {
			for (i = 0; i < pVector->capacity; i++)
				pVector->data[i] = NULL;
		}
	}
	return pVector;
}
//add item
Status g_vector_push_back(G_VECTOR hVector, Item item) {
	G_Vector* pVector = (G_Vector*)hVector;
	Item_ptr temp;
	int i;

	if (pVector->size >= pVector->capacity) {
		temp = (Item_ptr)malloc(sizeof(Item) * 2 * pVector->capacity);
		if (temp == NULL) {
			return FAILURE;
		}
		for (i = 0; i < pVector->capacity; i++) {
			temp[i] = pVector->data[i];
		}
		pVector->capacity *= 2;
		for (i = pVector->size; i < pVector->capacity; i++) {
			temp[i] = NULL;
		}
		free(pVector->data);
		pVector->data = temp;
	}
	pVector->item_assign(&pVector->data[pVector->size], item);
	pVector->size++;
	return SUCCESS;
}

//delete item
Status g_vector_pop_back(G_VECTOR hVector) {
	G_Vector* pVector = (G_Vector*)hVector;
	if (pVector->size <= 0) {
		return FAILURE;
	}
	pVector->size--;
	return SUCCESS;
}
//see a particular value
Item g_vector_at(G_VECTOR hVector, int index) {
	G_Vector* pVector = (G_Vector*)hVector;
	if (index < 0 || index >= pVector->capacity) {
		return NULL;
	}
	return pVector->data[index];
}
// return size and capacity
int  g_vector_get_size(G_VECTOR hVector) {
	G_Vector* pVector = (G_Vector*)hVector;
	return pVector->size;
}
int  g_vector_get_capacity(G_VECTOR hVector) {
	G_Vector* pVector = (G_Vector*)hVector;
	return pVector->capacity;
}

void  g_vector_destroy(G_VECTOR* phG_Vector) {
	G_Vector* pVector = (G_Vector*)*phG_Vector;
	
	for (int i = 0; i < pVector->size; i++)
	{
		pVector->item_destroy(&(pVector->data[i]));
	}
	free(pVector->data);
	free(pVector);
	*phG_Vector = NULL;
}

Status g_vector_assignment(Item_ptr phLeft, Item hRight) {
	G_Vector* pLeft = *phLeft;
	G_Vector* pRight = hRight;
	int i;
	if (pLeft == NULL)
	{
		pLeft = (G_Vector*)malloc(sizeof(G_Vector));
		if (pLeft == NULL)
		{
			return FAILURE;
		}
		else {
			*phLeft = pLeft;
		}
	}
	pLeft->size = pRight->size;
	pLeft->capacity = pRight->capacity;
	free(pLeft->data);
	pLeft->data = (Item_ptr)malloc(sizeof(Item) * pLeft->capacity);
	pLeft->item_assign = pRight->item_assign;
	pLeft->item_destroy = pRight->item_destroy;
	// copy everything from right's data into left's data
	for (i = 0; i < pRight->capacity; i++)
	{
		pLeft->data[i] = NULL; // always set to NULL first
		if (i < pRight->size) { // sometimes try to copy data
			pRight->item_assign(&(pLeft->data[i]), pRight->data[i]);
		}
	}
	
	return SUCCESS;
}
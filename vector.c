#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

struct gen_vector {
	int size;
	int capacity;
	Item_ptr data;
	Status(*item_assignment)(Item_ptr, Item);
	void(*item_destroy)(Item_ptr);
};
typedef struct gen_vector Gen_vector;

GEN_VECTOR gen_vector_init_default(Status(*item_assignment)(Item_ptr, Item), void(*item_destroy)(Item_ptr)) {
	
	Gen_vector* pVector = NULL;
	pVector = (Gen_vector*)malloc(sizeof(Gen_vector));
	
	if (pVector != NULL) {
		pVector->size = 0;
		pVector->capacity = 4;
		pVector->data = (void**)malloc(sizeof(void*)*pVector->capacity);
		
		if (pVector->data == NULL) {
			free(pVector);
			pVector = NULL;
		}
		else {
			for (int i = 0; i < pVector->capacity; i++) {
				pVector->data[i] = NULL;
			}
			pVector->item_assignment = item_assignment;
			pVector->item_destroy = item_destroy;
		}
	}
	return pVector;
}

Status gen_vector_push_back(GEN_VECTOR hVector, Item hItem) {
	Gen_vector* pVector = (Gen_vector*)hVector;

	if (pVector->size >= pVector->capacity) {
		Item_ptr temp = NULL;
		temp = (Item*)malloc(sizeof(Item)*pVector->capacity * 2);

		if (temp == NULL) {
			return FAILURE;
		}

		for (int i = 0; i < pVector->capacity * 2; i++) {
			if (i < pVector->capacity) {
				temp[i] = pVector->data[i];
			}
			else {
				temp[i] = NULL;
			}
		}
		free(pVector->data);
		pVector->data = temp;
		pVector->capacity *= 2;
	}
	
	Item* addr_to_edit = &pVector->data[pVector->size];

	pVector->item_assignment(addr_to_edit, hItem);
	pVector->size++;

	return SUCCESS;
}

void gen_vector_destroy(GEN_VECTOR* phVector) {
	Gen_vector* pVector = (Gen_vector*)*phVector;

	if (pVector->size != 0) {
		for (int i = 0; i < pVector->size; i++) {
			pVector->item_destroy(&pVector->data[i]);
		}
	}

	free(pVector->data);
	free(pVector);
	*phVector = NULL;
}

int gen_vector_get_size(GEN_VECTOR hVector) {
	Gen_vector* pVector = (Gen_vector*)hVector;
	return pVector->size;
}

int gen_vector_get_capacity(GEN_VECTOR hVector) {
	Gen_vector* pVector = (Gen_vector*)hVector;
	return pVector->capacity;
}

Item gen_vector_at(GEN_VECTOR hVector, int index) {
	Gen_vector* pVector = (Gen_vector*)hVector;
	if (index < 0 || index >= pVector->size) {
		return NULL;
	}
	return pVector->data[index];
}


Status gen_vector_pop_back(GEN_VECTOR hVector) {
	Gen_vector* pVector = (Gen_vector*)hVector;
	if (pVector->size <= 0) {
		return FAILURE;
	}
	pVector->size--;
	return SUCCESS;
}

Status gen_vector_assignment(Item_ptr phLeft, Item hRight) {
	// cast Item Right to have My_string typing
	Gen_vector *pRight = (Gen_vector*)hRight;
	Gen_vector *pLeft = (Gen_vector*)*phLeft;
	// if object in address held by pLeft is NULL
	// create a new my_string , then deep copy Right into it
	if (pLeft == NULL) {
		pLeft = (Gen_vector*)malloc(sizeof(Gen_vector));
		if (pLeft != NULL)
		{
			*phLeft = pLeft;
			pLeft->size = pRight->size;
			pLeft->capacity = pRight->capacity;
			pLeft->data = (void**)malloc(sizeof(void*) * pLeft->capacity);
			if (pLeft->data == NULL)
			{
				free(pLeft);
				pLeft = NULL;
			}
			else {
				int i;
				for (i = 0; i < pLeft->size; i++) {
					pLeft->data[i] = pRight->data[i];
				}
				for (i; i < pLeft->capacity; i++) {
					pLeft->data[i] = NULL;
				}
			}
			pLeft->item_assignment = pRight->item_assignment;
			pLeft->item_destroy = pRight->item_destroy;
		}
	}
	// else deep copy Right into *pLeft, freeing and resizing if necessary
	else {

		// only free and reallocate memory if capacities differ
		if (pLeft->capacity != pRight->capacity) {
			free(pLeft->data);

			pLeft->size = pRight->size;
			pLeft->capacity = pRight->capacity;
			pLeft->data = (Item *)malloc(sizeof(Item) * pLeft->capacity);

			for (int i = 0; i < pLeft->size; i++) {
				pLeft->data[i] = pRight->data[i];
			}
		}
		else {
			pLeft->size = pRight->size;
			int i;
			for (i = 0; i < pLeft->size; i++) {
				pLeft->data[i] = pRight->data[i];
			}
			for (i; i < pLeft->capacity; i++) {
				pLeft->data[i] = NULL;
			}
		}
	}
	return SUCCESS;
}
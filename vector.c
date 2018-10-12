#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

struct gen_vector {
	int size;
	int capacity;
	Item* data;
	Status(*item_assignment)(Item*, Item);
	void(*item_destroy)(Item*);
};
typedef struct gen_vector Gen_vector;

GEN_VECTOR gen_vector_init_default(Status(*item_assignment)(Item*, Item), void(*item_destroy)(Item*)) {
	
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
		Item* temp_arr = NULL;
		temp_arr = (Item*)malloc(sizeof(Item)*pVector->capacity * 2);

		if (temp_arr == NULL) {
			return FAILURE;
		}

		for (int i = 0; i < pVector->capacity * 2; i++) {
			if (i < pVector->capacity) {
				temp_arr[i] = pVector->data[i];
			}
			else {
				temp_arr[i] = NULL;
			}
		}
		free(pVector->data);
		pVector->data = temp_arr;
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

/*
Status vector_pop_back(VECTOR hVector) {
	Gen_vector* pVector = (Gen_vector*)hVector;
	if (pVector->size <= 0) {
		return FAILURE;
	}
	pVector->size--;
	return SUCCESS;
}









*/
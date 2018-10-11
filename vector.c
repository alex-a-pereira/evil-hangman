#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

struct vector {
	int size;
	int capacity;
	MY_STRING* data;
};
typedef struct vector Vector;

VECTOR vector_init_default(void) {
	Vector* pVector = NULL;
	pVector = (Vector*)malloc(sizeof(Vector));
	if (pVector != NULL) {
		pVector->size = 0;
		pVector->capacity = 4;
		pVector->data = (MY_STRING*)malloc(sizeof(MY_STRING)*pVector->capacity);
		if (pVector->data == NULL) {
			free(pVector);
			pVector = NULL;
		}
		else {
			for (int i = 0; i < pVector->capacity; i++) {
				pVector->data[i] = NULL;
			}
		}
	}
	return pVector;
}

Status vector_push_back(VECTOR hVector, Item hItem) {
	Vector* pVector = (Vector*)hVector;
	MY_STRING* pMy_string = (MY_STRING*)hItem;

	int i;
	if (pVector->size >= pVector->capacity) {
		MY_STRING* temp_arr = NULL;
		temp_arr = (MY_STRING*)malloc(sizeof(MY_STRING)*pVector->capacity * 2);

		if (temp_arr == NULL) {
			return FAILURE;
		}
		
		for (i = 0; i < pVector->capacity; i++) {
			temp_arr[i] = pVector->data[i];
		}
		for (i; i < (pVector->capacity * 2); i++) {
			temp_arr[i] = NULL;
		}

		free(pVector->data);
		pVector->data = temp_arr;
		pVector->capacity *= 2;
	}
	MY_STRING* addr_to_edit = &pVector->data[pVector->size];
	my_string_assignment(addr_to_edit, pMy_string);

	pVector->size++;

	return SUCCESS;
}

Status vector_pop_back(VECTOR hVector) {
	Vector* pVector = (Vector*)hVector;
	if (pVector->size <= 0) {
		return FAILURE;
	}
	pVector->size--;
	return SUCCESS;
}

int vector_get_size(VECTOR hVector) {
	Vector* pVector = (Vector*)hVector;
	return pVector->size;
}

int vector_get_capacity(VECTOR hVector) {
	Vector* pVector = (Vector*)hVector;
	return pVector->capacity;
}

MY_STRING vector_at(VECTOR hVector, int index) {
	Vector* pVector = (Vector*)hVector;
	if (index < 0 || index >= pVector->size) {
		return NULL;
	}
	return pVector->data[index];
}


void vector_destroy(VECTOR* phVector) {
	Vector* pVector = (Vector*)*phVector;
	free(pVector->data);
	free(pVector);
	*phVector = NULL;
}

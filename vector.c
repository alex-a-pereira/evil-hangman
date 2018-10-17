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
		temp = (Item_ptr)malloc(sizeof(Item)*pVector->capacity * 2);

		if (temp == NULL) {
			printf("FAIL\n");
			return FAILURE;
		}

		for (int i = 0; i < pVector->size; i++) {
			temp[i] = pVector->data[i];
		}
		for (int i = pVector->size; i < pVector->capacity * 2; i++) {
			temp[i] = NULL;
		}

		free(pVector->data);
		pVector->data = temp;
		pVector->capacity *= 2;
	}

	Item_ptr addr_to_edit = &(pVector->data[pVector->size]);

	pVector->item_assignment(addr_to_edit, hItem);
	pVector->size++;

	return SUCCESS;
}

void gen_vector_destroy(GEN_VECTOR* phVector) {
	Gen_vector* pVector = (Gen_vector*)*phVector;
	
	if (pVector->size != 0) {
		for (int i = 0; i < pVector->size; i++) {
			Item_ptr addr_to_destroy = &pVector->data[i];
			pVector->item_destroy(addr_to_destroy);
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
		printf("too large\n");
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
	Gen_vector *pGen_vector_left = (Gen_vector*)*phLeft;
	// if object in address held by pLeft is NULL
	// create a new my_string , then deep copy Right into it
	if (pGen_vector_left == NULL) {
		Gen_vector *pNew_gen_vector = NULL;
		pNew_gen_vector = (Gen_vector*)malloc(sizeof(Gen_vector));
		
		if (pNew_gen_vector != NULL)
		{
			*phLeft = pNew_gen_vector;
			pNew_gen_vector->size = pRight->size;
			pNew_gen_vector->capacity = pRight->capacity;
			pNew_gen_vector->data = (void**)malloc(sizeof(void*) * pNew_gen_vector->capacity);
			
			if (pNew_gen_vector->data == NULL)
			{
				printf("FAILURE\n");
				free(pNew_gen_vector);
				pNew_gen_vector = NULL;
			}
			else {
				int i;
				for (i = 0; i < pRight->capacity; i++) {
					pNew_gen_vector->data[i] = pRight->data[i];
				}
			}
			pNew_gen_vector->item_assignment = pRight->item_assignment;
			pNew_gen_vector->item_destroy = pRight->item_destroy;
		}
		else {
			printf("FAILURE\n");
		}
	}
	// else deep copy Right into *pLeft, freeing and resizing if necessary
	else {
		Gen_vector *pGen_vector_left = (Gen_vector*)*phLeft;
		// only free and reallocate memory if capacities differ
		if (pGen_vector_left->capacity != pRight->capacity) {
			free(pGen_vector_left->data);

			pGen_vector_left->size = pRight->size;
			pGen_vector_left->capacity = pRight->capacity;
			pGen_vector_left->data = (Item *)malloc(sizeof(Item) * pGen_vector_left->capacity);

			for (int i = 0; i < pGen_vector_left->size; i++) {
				pGen_vector_left->data[i] = pRight->data[i];
			}
		}
		else {
			pGen_vector_left->size = pRight->size;
			int i;
			for (i = 0; i < pGen_vector_left->capacity; i++) {
				pGen_vector_left->data[i] = pRight->data[i];
			}
		}
	}
	return SUCCESS;
}
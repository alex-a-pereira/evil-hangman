#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

struct my_string
{
	int size;
	int capacity;
	char *data;
};
typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
	My_string *pMy_string = NULL;
	pMy_string = (My_string *)malloc(sizeof(My_string));

	if (pMy_string != NULL)
	{
		pMy_string->size = 0;
		pMy_string->capacity = 7;
		pMy_string->data = (char*)malloc(sizeof(char) * 7);

		if (pMy_string->data == NULL)
		{
			free(pMy_string);
			pMy_string = NULL;
		}
	}
	return pMy_string;
}

MY_STRING my_string_init_c_string(const char *c_string)
{
	int len_c_string = 0;
	while (c_string[len_c_string] != '\0')
	{
		len_c_string++;
	}
	len_c_string++;

	My_string *pMy_string = NULL;
	pMy_string = (My_string *)malloc(sizeof(My_string));

	if (pMy_string != NULL)
	{
		pMy_string->size = len_c_string - 1;
		pMy_string->capacity = len_c_string;
		pMy_string->data = (char *)malloc(sizeof(char) * pMy_string->capacity);

		if (pMy_string->data == NULL)
		{
			free(pMy_string);
			pMy_string = NULL;
		}

		for (int i = 0; i < len_c_string; i++)
		{
			pMy_string->data[i] = c_string[i];
		}
	}
	return pMy_string;
}

Status my_string_push_back(MY_STRING hMy_string, char item) {
	My_string *pMy_string = (My_string *)hMy_string;

 	if (pMy_string->size + 1 == pMy_string->capacity)
	{
		int old_size = pMy_string->capacity - 1;

		char* temp_data1 = (char *)malloc(sizeof(char) * old_size);
		for (int i = 0; i < old_size; i++) {
			temp_data1[i] = pMy_string->data[i];
		}

		free(pMy_string->data);

		pMy_string->capacity = (old_size * 2) + 1;
		pMy_string->data = (char *)malloc(sizeof(char) * (pMy_string->capacity));

		if (pMy_string->data == NULL) {
			return FAILURE;
		}

		for (int i = 0; i < old_size; i++) {
			pMy_string->data[i] = temp_data1[i];
		}

		free(temp_data1);
	}
	pMy_string->size++;
	pMy_string->data[pMy_string->size - 1] = item;

	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
	My_string *pMy_string = (My_string *)hMy_string;

	if (pMy_string->size == 0) {
		return FAILURE;
	}
	else {
		pMy_string->size--;
		return SUCCESS;
	}
}

int my_string_get_size(MY_STRING hMy_string)
{
	My_string *pMy_string = (My_string *)hMy_string;
	return pMy_string->size;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
	My_string *pMy_string = (My_string *)hMy_string;
	return pMy_string->capacity;
}

Boolean my_string_empty(MY_STRING hMy_string) {
	My_string *pMy_string = (My_string *)hMy_string;

	if (pMy_string->size == 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

char* my_string_at(MY_STRING hMy_string, int index) {
	My_string *pMy_string = (My_string *)hMy_string;

	if (index < 0 || index >= pMy_string->size) {
		return NULL;
	}
	else {
		char* pChar = pMy_string->data + index;
		return pChar;
	}
}

char* my_string_c_str(MY_STRING hMy_string) {
	My_string *pMy_string = (My_string *)hMy_string;

	if (pMy_string->size == 0) {
		return NULL;
	}
	else {
		pMy_string->data[pMy_string->size] = '\0';
		char* pChar = pMy_string->data;
		return pChar;
	}
}

Status my_string_extraction(MY_STRING hMy_string, FILE *fp)
{
	My_string *pMy_string = (My_string *)hMy_string;

	if (pMy_string->size > 0) {
		free(pMy_string->data);
		pMy_string->size = 0;
		pMy_string->data = (char *)malloc(sizeof(char) * pMy_string->capacity);
	}

	char ch_from_file = fgetc(fp);

	if (ch_from_file == EOF)
	{
		return FAILURE;
	}

	while (isspace(ch_from_file) || ch_from_file == EOF)
	{
		ch_from_file = fgetc(fp);
		if (ch_from_file == EOF)
		{
			return FAILURE;
		}
	}

	int ch_count = 0;

	while (!(isspace(ch_from_file) || ch_from_file == EOF))
	{
		if (ch_count == pMy_string->capacity - 1) {
			int old_size = pMy_string->capacity - 1;

			char* temp_data1 = (char *)malloc(sizeof(char) * old_size);

			for (int i = 0; i < ch_count; i++) {
				temp_data1[i] = pMy_string->data[i];
			}

			free(pMy_string->data);

			pMy_string->capacity = (old_size * 2) + 1;
			pMy_string->data = (char *)malloc(sizeof(char) * (pMy_string->capacity));

			if (pMy_string->data == NULL) {
				return FAILURE;
			}

			for (int i = 0; i < old_size; i++) {
				pMy_string->data[i] = temp_data1[i];
			}

			free(temp_data1);
		}
		pMy_string->data[ch_count] = ch_from_file;
		ch_from_file = fgetc(fp);
		ch_count++;
	}

	pMy_string->size = ch_count;

	fseek(fp, -1, SEEK_CUR);
	return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE *fp)
{
	My_string *pMy_string = (My_string *)hMy_string;
	int i = 0;

	while (i < pMy_string->size) {
		fprintf(fp, "%c", pMy_string->data[i]);
		i++;
	}
	printf("\n");
	return FAILURE;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string *pLeft_string = (My_string *)hLeft_string;
	My_string *pRight_string = (My_string *)hRight_string;

	char *left_string_data = pLeft_string->data;
	char *right_string_data = pRight_string->data;

	int left_string_size = pLeft_string->size;
	int right_string_size = pRight_string->size;

	int i = 0;

	while ((i < left_string_size) && (i < right_string_size))
	{

		if (left_string_data[i] == right_string_data[i])
		{

			if ((i + 1 == left_string_size) && (i + 1 != right_string_size))
			{
				return -1;
			}
			else if ((i + 1 != left_string_size) && (i + 1 == right_string_size))
			{
				return 1;
			}
			else
			{
				i++;
				continue;
			}
		}
		else if (left_string_data[i] > right_string_data[i])
		{
			return 1;
		}
		else if (left_string_data[i] < right_string_data[i])
		{
			return -1;
		}
		i++;
	}
	return 0;
}
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {
	My_string *pResult = (My_string *)hResult;
	My_string *pAppend = (My_string *)hAppend;

	if (pResult->size + pAppend->size >= (pResult->capacity)) {
		return FAILURE;
	}
	else {
		int index_offset = pResult->size;
		for (int i = 0; i < pAppend->size; i++) {
			pResult->data[index_offset + i] = pAppend->data[i];
			pResult->size++;
		}
		return SUCCESS;
	}
}

void my_string_destroy(Item_ptr pItem)
{
	My_string *pMy_string = (My_string *)*pItem;
	free(pMy_string->data);
	free(pMy_string);
	*pItem = NULL;
}

Status my_string_assignment(Item_ptr pLeft, Item Right) {
	My_string *pMy_string_right = (My_string *)Right;
	My_string *pMy_string_left = (My_string *)*pLeft;

	if (pMy_string_left == NULL) {
		My_string *pMy_string_new = NULL;
		pMy_string_new = (My_string *)malloc(sizeof(My_string));

		if (pMy_string_new != NULL)
		{
			*pLeft = pMy_string_new;
			pMy_string_new->size = pMy_string_right->size;
			pMy_string_new->capacity = pMy_string_right->capacity;
			pMy_string_new->data = (char*)malloc(sizeof(char) * pMy_string_new->capacity);

			if (pMy_string_new->data == NULL)
			{
				printf("FAILURE\n");
				free(pMy_string_new);
				pMy_string_new = NULL;
			}
			else {
				for (int i = 0; i < pMy_string_new->size; i++) {
					pMy_string_new->data[i] = pMy_string_right->data[i];
				}
			}
		}
		else {
			printf("FAILURE\n");
		}
		
	}

	else {
		My_string *pMy_string_left = (My_string *)*pLeft;

		if (pMy_string_left->capacity != pMy_string_right->capacity) {
			free(pMy_string_left->data);

			pMy_string_left->size = pMy_string_right->size;
			pMy_string_left->capacity = pMy_string_right->capacity;
			pMy_string_left->data = (char *)malloc(sizeof(char) * pMy_string_left->capacity);
			
			for (int i = 0; i < pMy_string_left->size; i++) {
				pMy_string_left->data[i] = pMy_string_right->data[i];
			}
		}
		else {
			pMy_string_left->size = pMy_string_right->size;

			for (int i = 0; i < pMy_string_left->size; i++) {
				pMy_string_left->data[i] = pMy_string_right->data[i];
			}
		}
	}
	return SUCCESS;
}

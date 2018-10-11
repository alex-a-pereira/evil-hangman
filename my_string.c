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

//
// INIT
//
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
	// bring length up to actual length, which is max idx + 1
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
//
// PUSH and POP
//
Status my_string_push_back(MY_STRING hMy_string, char item) {
	My_string *pMy_string = (My_string *)hMy_string;

	// handle non alpha character
	if (item < 65 || (item > 90 && item < 97) || item > 122) {
		return FAILURE;
	}

	// handle case where no room is available in the string
	if (pMy_string->size + 1 == pMy_string->capacity)
	{
		int old_size = pMy_string->capacity - 1;

		char* temp_data1 = (char *)malloc(sizeof(char) * old_size);
		for (int i = 0; i < old_size; i++) {
			temp_data1[i] = pMy_string->data[i];
		}

		free(pMy_string->data);

		// update string capacity and dynamically increased allocate memory
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
// POP
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


// GET SIZE
int my_string_get_size(MY_STRING hMy_string)
{
	My_string *pMy_string = (My_string *)hMy_string;
	return pMy_string->size;
}
// GET CAPACITY
int my_string_get_capacity(MY_STRING hMy_string)
{
	My_string *pMy_string = (My_string *)hMy_string;
	return pMy_string->capacity;
}
// EMPTY
Boolean my_string_empty(MY_STRING hMy_string) {
	My_string *pMy_string = (My_string *)hMy_string;

	if (pMy_string->size == 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// GET CHAR
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
//
// GET C STRING
//
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
//
// EXTRACTION from file
//
Status my_string_extraction(MY_STRING hMy_string, FILE *fp)
{
	My_string *pMy_string = (My_string *)hMy_string;

	// clear previous values from data, if they exist
	if (pMy_string->size > 0) {
		free(pMy_string->data);
		pMy_string->size = 0;
		pMy_string->data = (char *)malloc(sizeof(char) * pMy_string->capacity);
	}

	// parse past leading whitespace
	char ch_from_file = fgetc(fp);

	// return false when the end of file is reached
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

			// update string capacity and dynamically increased allocate memory
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
		// Store new char into my_string and increment size
		pMy_string->data[ch_count] = ch_from_file;
		// get next character and increment counter
		ch_from_file = fgetc(fp);
		ch_count++;
	}

	// update size to accurately reflect the number of characters
	pMy_string->size = ch_count;

	// move cursor back to allow next iteration to parse cleanly
	fseek(fp, -1, SEEK_CUR);
	return SUCCESS;
}

// INSERTION to file
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
//
// COMPARE
//
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
			// Since we've made it this far, all chars are the same so far.
			// if next current index + 1 == size of left str but not size of right str,
			// left str is shorter.
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
	// only make it this far if we iterate to the maximum index of both strings
	return 0;
}
//
// CONCAT
//
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
//
// DESTROY
//
void my_string_destroy(Item *pItem)
{
	My_string *pMy_string = (My_string *)*pItem;
	free(pMy_string->data);
	free(pMy_string);
	*pItem = NULL;
}
//
// ASSIGNMENT
//
void my_string_assignment(Item* pLeft, Item Right) {
	// cast Item Right to have My_string typing
	My_string *pMy_string_right = (My_string *)Right;

	// if object in address held by pLeft is NULL
	// create a new my_string , then deep copy Right into it
	if (*pLeft == NULL) {
		My_string *pMy_string_new = NULL;
		pMy_string_new = (My_string *)malloc(sizeof(My_string));

		if (pMy_string_new != NULL)
		{
			pMy_string_new->size = pMy_string_right->size;
			pMy_string_new->capacity = pMy_string_right->capacity;
			pMy_string_new->data = (char*)malloc(sizeof(char) * pMy_string_new->capacity);

			if (pMy_string_new->data == NULL)
			{
				free(pMy_string_new);
				pMy_string_new = NULL;
			}
			else {
				for (int i = 0; i < pMy_string_new->size; i++) {
					pMy_string_new->data[i] = pMy_string_right->data[i];
				}
			}
		}
		*pLeft = pMy_string_new;
	}
	// else deep copy Right into *pLeft, freeing and resizing if necessary
	else {
		My_string *pMy_string_left = (My_string *)*pLeft;

		// only free and reallocate memory if capacities differ
		if (pMy_string_left->capacity != pMy_string_right->capacity) {
			free(pMy_string_left->data);

			pMy_string_left->size = pMy_string_right->size;
			pMy_string_left->capacity = pMy_string_right->capacity;
			pMy_string_left->data = (char *)malloc(sizeof(char) * pMy_string_left->capacity);
			// ???????????????????????
			// What to do if pMy_string_left is NULL????
			// ???????????????????????
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
}

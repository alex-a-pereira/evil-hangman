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
	printf("my string default size and cap, %d %d\n", pMy_string->size, pMy_string->capacity);
	return pMy_string;
}

void my_string_destroy(MY_STRING *phMy_string)
{
	My_string *pMy_string = (My_string *)*phMy_string;
	free(pMy_string->data);
	free(pMy_string);
	*phMy_string = NULL;
	Status my_string_extraction(MY_STRING hMy_string, FILE * fp);
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

	printf("My string: %s, size: %d, capacity: %d\n", pMy_string->data, pMy_string->size, pMy_string->capacity);
	printf("\n");
	return pMy_string;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
	My_string *pMy_string = (My_string *)hMy_string;
	return pMy_string->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
	My_string *pMy_string = (My_string *)hMy_string;
	return pMy_string->size;
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
				return -1;
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
	/* we only make it this far if we iterate to the maximum index of
	*  the smaller string
	*/
	return 0;
}

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

Status my_string_insertion(MY_STRING hMy_string, FILE *fp)
{
	My_string *pMy_string = (My_string *)hMy_string;
	int i = 0;

	while (i < pMy_string->size) {
		fprintf(fp, "%c", pMy_string->data[i]);
		i++;
	}

	return FAILURE;
}

Status my_string_push_back(MY_STRING hMy_string, char item) {
	My_string *pMy_string = (My_string *)hMy_string;

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

Status my_string_pop_back(MY_STRING hMy_string) 
{
	My_string *pMy_string = (My_string *)hMy_string;
	
	if (pMy_string->size == 0) {
		return FAILURE;
	}
	else {
		pMy_string->size --;
		return SUCCESS;
	}
}

char* my_string_at(MY_STRING hMy_string, int index) {
	My_string *pMy_string = (My_string *)hMy_string;
	
	if (index < 0 || index >= pMy_string->size) {
		return FAILURE;
	}
	else {
		char* pChar = pMy_string->data + index;
		return pChar;
	}	
}

char* my_string_c_str(MY_STRING hMy_string) {
	My_string *pMy_string = (My_string *)hMy_string;

	if (pMy_string->size == 0) {
		return FAILURE;
	}
	else {
		pMy_string->data[pMy_string->size] = '\0';
		char* pChar = pMy_string->data;
		return pChar;
	}
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

Boolean my_string_empty(MY_STRING hMy_string) {
	My_string *pMy_string = (My_string *)hMy_string;

	if (pMy_string->size == 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}


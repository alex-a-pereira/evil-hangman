#include <stdio.h>
#include <stdlib.h>
#include "./my_string.h"

int main(int argc, char* argv[]) {
	MY_STRING hMy_string = NULL;
	// FILE* fp;
	hMy_string = my_string_init_default();
	
	Status truth = my_string_push_back(hMy_string, 'a');
	printf("%d\n", truth);
	truth = my_string_push_back(hMy_string, 'b');
	printf("%d\n", truth);
	Status popTruth = my_string_pop_back(hMy_string);
	printf("%d\n", popTruth);
	truth = my_string_push_back(hMy_string, 'b');
	printf("%d\n", truth);
	truth = my_string_push_back(hMy_string, 'c');
	printf("%d\n", truth);

	my_string_at(hMy_string, 0);
	my_string_c_str(hMy_string);

	MY_STRING hMy_string1 = NULL;
	hMy_string1 = my_string_init_default();

	my_string_push_back(hMy_string1, 'z');
	my_string_push_back(hMy_string1, 'y');
	my_string_push_back(hMy_string1, 'x');

	Status concatTruth = my_string_concat(hMy_string, hMy_string1);
	printf("%d\n", concatTruth);
	printf("%s\n", my_string_c_str(hMy_string));

	Boolean isEmpty = my_string_empty(hMy_string);
	printf("Empty: %d\n", isEmpty);

	popTruth = my_string_pop_back(hMy_string);
	printf("Pop successful: %d\n", popTruth);
	popTruth = my_string_pop_back(hMy_string);
	printf("Pop successful: %d\n", popTruth);
	popTruth = my_string_pop_back(hMy_string);
	printf("Pop successful: %d\n", popTruth);
	popTruth = my_string_pop_back(hMy_string);
	printf("Pop successful: %d\n", popTruth);
	popTruth = my_string_pop_back(hMy_string);
	printf("Pop successful: %d\n", popTruth);
	popTruth = my_string_pop_back(hMy_string);
	printf("Pop successful: %d\n", popTruth);

	isEmpty = my_string_empty(hMy_string);
	printf("Empty after pops: %d\n", isEmpty);

	/* 
	LAB 3
	fp = fopen("./simple.txt", "r");
	while (my_string_extraction(hMy_string, fp))
	{
		if (my_string_get_size(hMy_string) == 4) {
			my_string_insertion(hMy_string, stdout);
			printf("\n");
			if (fgetc(fp) == ' ')
			{
				printf("Found a space after the string\n");
			}
		}
	}
	*/


	my_string_destroy(&hMy_string);
	// fclose(fp);
	return 0;
}

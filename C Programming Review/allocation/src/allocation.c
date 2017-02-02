#include "../include/allocation.h"
#include <stdlib.h>
#include <stdio.h>

void* allocate_array(size_t member_size, size_t nmember,bool clear)
{
	if(member_size == 0 || nmember == 0) return NULL;
	if(clear) return calloc(nmember, member_size); //Calloc if clear = 1

	return malloc(member_size*nmember); //Malloc if clear = 0

}

void* reallocate_array(void* ptr, size_t size)
{
	if(ptr == NULL) return NULL;
	return realloc(ptr, size);
}

void deallocate_array(void** ptr)
{
	if(*ptr == NULL) return;
    /*deallocate by freeing the pointer and setting it to null*/
	free(*ptr);
	*ptr = NULL;
	return;
}

char* read_line_to_buffer(char* filename)
{
	if(filename == NULL) return NULL;
	
	FILE* file = fopen(filename, "r"); //Open file to read
	char* temp = malloc(sizeof(char)*BUFSIZ); //Character array to read line into
	fgets(temp, BUFSIZ, file);
	fclose(file); //close file pointer
	return temp;

}

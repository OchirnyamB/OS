#include "../include/allocation.h"
#include <stdlib.h>
#include <stdio.h>

void* allocate_array(size_t member_size, size_t nmember,bool clear)
{
	if(member_size == 0 || nmember == 0) return NULL;
	if(clear) return calloc(nmember, member_size);

	return malloc(member_size*nmember);

}

void* reallocate_array(void* ptr, size_t size)
{
	if(ptr == NULL || size <= 0) return NULL;
	return realloc(ptr, size);
}

void deallocate_array(void** ptr)
{
	if(*ptr == NULL) return;
	free(*ptr);
	*ptr = NULL;
	return;
}

char* read_line_to_buffer(char* filename)
{
	if(filename == NULL) return NULL;
	
	FILE* file = fopen(filename, "r");
	char* temp = malloc(sizeof(char)*BUFSIZ);
	fgets(temp, BUFSIZ, file);
	fclose(file);
	return temp;

}

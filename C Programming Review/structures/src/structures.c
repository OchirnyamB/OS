
#include "../include/structures.h"
#include <stdio.h>

int compare_structs(sample_t* a, sample_t* b)
{
	if(a->a != b->a || a->b != b->b || a->c != b->c) return 0;
	return 1;
}

void print_alignments()
{
	printf("Alignment of int is %zu bytes\n",__alignof__(int));
	printf("Alignment of double is %zu bytes\n",__alignof__(double));
	printf("Alignment of float is %zu bytes\n",__alignof__(float));
	printf("Alignment of char is %zu bytes\n",__alignof__(char));
	printf("Alignment of long long is %zu bytes\n",__alignof__(long long));
	printf("Alignment of short is %zu bytes\n",__alignof__(short));
	printf("Alignment of structs are %zu bytes\n",__alignof__(fruit_t));
}

int sort_fruit(const fruit_t* a,int* apples,int* oranges, const size_t size)
{
	size_t i; 
	for(i = 0; i < size; i ++) a[i].type == 1 ? apples[0]++ : oranges[0]++;
	return size;
	
}

int initialize_array(fruit_t* a, int apples, int oranges)
{
	int size = apples + oranges;
	for(int i = 0; i < size - apples; i++) a[i].type = 0;
	for(int i = size - apples; i < size; i++) a[i].type = 1;
	return 0;
}

int initialize_orange(orange_t* a)
{
	return 0;

}

int initialize_apple(apple_t* a)
{
	return 0;
}

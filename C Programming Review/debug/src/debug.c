#include "../include/debug.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// protected function, that only this .c can use
int comparator_func(const void *a, const void *b) {
    return ( *(uint16_t*)a - *(uint16_t*)b );
}

bool terrible_sort(uint16_t *data_array, const size_t value_count) {
    if(data_array == NULL || value_count == 0) return false;

    uint16_t* sorting_array= malloc(value_count * sizeof(uint16_t));

    for (int i = 0; i < (int)value_count; ++i) sorting_array[i] = data_array[i];
    
    qsort(sorting_array, value_count, sizeof(uint16_t), comparator_func);

    bool sorted = true;

    memcpy(data_array, sorting_array, value_count*sizeof(uint16_t));
    free(sorting_array);

    return sorted;
}


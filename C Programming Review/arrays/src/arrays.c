/**
 * Name: Ali Raza
 * OS Operating Systems
 * C Refresher Assignment
 * January 23, 2017
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"

// LOOK INTO MEMCPY, MEMCMP, FREAD, and FWRITE

bool array_copy(const void *src, void *dst, const size_t elem_size, const size_t elem_count) {

    //Byte count measures the total number of bytes in the array to be copied.
    size_t byte_count = elem_size * elem_count; 
   
    if(src == NULL || dst == NULL || byte_count == 0) return false;
    
    memcpy(dst, src, byte_count);

    return array_is_equal(src, dst, elem_size, elem_count);

}

bool array_is_equal(const void *data_one, void *data_two, const size_t elem_size, const size_t elem_count) {

    size_t byte_count = elem_size * elem_count;

    if(data_one == NULL || data_two == NULL || byte_count == 0) return false;
    
    if(!memcmp(data_one, data_two, byte_count)){
        return true;
    }

	return false;
}

ssize_t array_locate(const void *data, const void *target, const size_t elem_size, const size_t elem_count) {

    size_t byte_size = elem_size*elem_count;
    if(data == NULL || target == NULL || byte_size == 0) return -1;

    for(int i = 0; i < (int)elem_count; i++){
        if(memcmp(data, target, elem_size) == 0) return i;

        data = data + (elem_size);
    }

	return -1;
}

bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count) {
    
    size_t byte_size = elem_size * elem_count;
    if(dst_file == NULL || strcmp(dst_file, "\n") == 0 || strcmp(dst_file, "")==0 || byte_size == 0 || src_data == NULL) return false;
    
    FILE* fp = fopen(dst_file, "w");
    fwrite(src_data, elem_size, elem_count, fp);
    fclose(fp);

    return true;


}

bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count) {
    
    size_t byte_size = elem_size * elem_count;
    if(src_file == NULL || strcmp(src_file, "\n") == 0 || strcmp(src_file, "")==0 || byte_size == 0 || dst_data == NULL) return false;
    
    FILE* fp = fopen(src_file, "r");
    fread(dst_data, elem_size, elem_count, fp);
    fclose(fp);

	return true;
}

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/sys_prog.h"

// LOOK INTO OPEN, READ, WRITE, CLOSE, FSTAT/STAT, LSEEK
// GOOGLE FOR ENDIANESS HELP

bool bulk_read(const char *input_filename, void *dst, const size_t offset, const size_t dst_size) {

    if(input_filename == NULL || dst == NULL || !strcmp(dst, "\n") || !strcmp(dst, "\0") || offset > dst_size || dst_size == 0) return false;

    int descriptor = open(input_filename, O_RDWR);
    if(descriptor < 0) return false;
    
    size_t read_data; 

    if(offset == 0){
        read_data = read(descriptor, dst, dst_size-offset);
    } else {
        read_data = read(descriptor, dst, offset);
    }
    
    if(read_data < 0) return false;
 
    if(read_data == dst_size) return true;

	return false;
}

bool bulk_write(const void *src, const char *output_filename, const size_t offset, const size_t src_size) {

    if(output_filename == NULL || src == NULL || !strcmp(output_filename, "\n") || !strcmp(output_filename, "\0") || !strcmp(output_filename, "") || src_size == 0) return false;

    int descriptor = open(output_filename, O_WRONLY);
    if(descriptor < 0) return false;

    size_t write_data;

    if(offset == 0){
        write_data = write(descriptor, src, src_size-offset);
    } else if(offset > src_size) {
        write_data = write(descriptor, src, src_size);
        //return true;
    } else{
        write_data = write(descriptor, src, offset);
    }

    printf("%d\n", (int)write_data);

    if(write_data < 0) return false;

    if(write_data == src_size) return true;

	return false;
}


bool file_stat(const char *query_filename, struct stat *metadata) {

    if(query_filename == NULL || metadata == NULL) return false;

    if(stat(query_filename, metadata)) return false;

    stat(query_filename, metadata);
    return true;

}

bool endianess_converter(uint32_t *src_data, uint32_t *dst_data, const size_t src_count) {

    if(src_data == NULL || dst_data == NULL || src_count == 0) return false;

    for(size_t i =0; i < src_count; i++){
        uint32_t num = src_data[i];
        uint32_t b0, b1, b2, b3;

        b0 = (num & 0x000000ff) << 24u; //move byte 0 to 3
        b1 = (num & 0x0000ff00) << 8u; // move byte 1 to 2
        b2 = (num & 0x00ff0000) >> 8u; //move byte 2 to 1
        b3 = (num & 0xff000000) >> 24u; //move byte 3 to 0

        dst_data[i] = b0 | b1 | b2 | b3; //pipe all bytes
    }

	return true;
}

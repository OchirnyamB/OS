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

	return false;
}

bool endianess_converter(uint32_t *src_data, uint32_t *dst_data, const size_t src_count) {

	return false;
}

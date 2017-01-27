#include "../include/bitmap.h"
#include <math.h>

// data is an array of uint8_t and needs to be allocated in bitmap_create
// and used in the remaining bitmap functions. You will use data for any bit operations and bit logic
// bit_count the number of requested bits, set in bitmap_create from n_bits
// byte_count the total number of bytes the data contains, set in bitmap_create


bitmap_t *bitmap_create(size_t n_bits) {

	if(n_bits <=0) return NULL;

	bitmap_t *bitmap = malloc(n_bits);

	if(bitmap != NULL){
		bitmap->bit_count = n_bits;
		bitmap->byte_count = ceil(n_bits/8.0); //Byte count is the ceiling of n_bits/8
		bitmap->data = calloc(bitmap->byte_count, sizeof(*bitmap->data));
		if(bitmap->data == NULL){ //if the data failed to allocate free bitmap and indicate failure
			free(bitmap);
			return NULL;
		}
	} 
    return bitmap;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit) {

	if(bitmap == NULL || bit > bitmap->bit_count){
		return false;
	}

	int i = bit/8;            // i = array index (use: A[i])
    int pos = bit%8;          // pos = bit position in A[i]

    unsigned int flag = 1;   // flag = 0000.....00001
    flag = flag << pos;      // flag = 0000...010...000   (shifted k positions)
    bitmap->data[i] = bitmap->data[i] | flag;      // Set the bit at the k-th position in A[i]

	return true;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit) {

	if(bitmap == NULL || bit > bitmap->bit_count){
		return false;
	}

	int i = bit/8;
    int pos = bit%8;

    unsigned int flag = 1;  // flag = 0000.....00001

    flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)
    flag = ~flag;           // flag = 1111...101..111

    bitmap->data[i] = bitmap->data[i] & flag;     // RESET the bit at the k-th position in A[i]

	return true;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit) {
	if(bitmap == NULL || bit > bitmap->bit_count){
		return false;
	}

	int i = bit/8;
	int pos = bit%8;

	unsigned int flag = 1;  // flag = 0000.....00001

	flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)

	if ( bitmap->data[i] & flag ) return true;  // Test the bit at the k-th position in A[i]

	return false;
}

size_t bitmap_ffs(const bitmap_t *const bitmap) {

	if(bitmap == NULL) return SIZE_MAX;
	size_t i;

	//Iterate the bitmap with the bitmap test function. 
	for(i=0; i < bitmap->bit_count; i++){
		if(bitmap_test(bitmap,i)) return i;
	}

	return SIZE_MAX;
}

size_t bitmap_ffz(const bitmap_t *const bitmap) {

	if(bitmap == NULL) return SIZE_MAX;
	size_t i;

	//Iterate the bitmap with the bitmap test function. 
	for(i=0; i < bitmap->bit_count; i++){
		if(!bitmap_test(bitmap,i)) return i;
	}

	return SIZE_MAX;
}

bool bitmap_destroy(bitmap_t *bitmap) {

	if(bitmap == NULL) return false;

	free(bitmap->data);
	bitmap->data = NULL;
	free(bitmap);
	bitmap = NULL;

	return true;
}

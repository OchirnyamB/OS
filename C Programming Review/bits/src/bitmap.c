#include "../include/bitmap.h"

// data is an array of uint8_t and needs to be allocated in bitmap_create
//      and used in the remaining bitmap functions. You will use data for any bit operations and bit logic
// bit_count the number of requested bits, set in bitmap_create from n_bits
// byte_count the total number of bytes the data contains, set in bitmap_create


bitmap_t *bitmap_create(size_t n_bits) {

	if(n_bits ==0) return NULL;

	bitmap_t *bitmap = malloc(sizeof(*bitmap));

	if(bitmap != NULL){

		bitmap->bit_count = n_bits;

		size_t n_bytes = n_bits / 8;
		if(n_bits % 8){
			n_bytes++;
		}

		bitmap->byte_count = n_bytes;

		bitmap->data = calloc(bitmap->byte_count, sizeof(*bitmap->data));
		
		if(bitmap->data == NULL){
			free(bitmap);
			bitmap = NULL;
		}
	}

    return bitmap;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit) {

	return false;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit) {

	return false;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit) {
	return false;
}

size_t bitmap_ffs(const bitmap_t *const bitmap) {

	return 0;
}

size_t bitmap_ffz(const bitmap_t *const bitmap) {

	return 0;
}

bool bitmap_destroy(bitmap_t *bitmap) {
	return false;
}

/**
 * Name: Ali Raza
 * CS 4520: Block Storage Assignment
 * Date Created: 02/14/2017
 * Last Modified: 02/16/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "block_store.h"
#include "bitmap.h"

#define block_size 256

typedef struct block_store{
    char* data[block_size-1][block_size-1];
    bitmap_t* bitmap;
} block_store_t;

block_store_t *block_store_create(){
    
    block_store_t* newBlockStore = malloc(sizeof(block_store_t));
    if(newBlockStore != NULL){ //if malloc doesn't fail
        newBlockStore->bitmap = bitmap_create(block_size-1);
        return newBlockStore;
    } 
    return NULL;
}

void block_store_destroy(block_store_t *const bs){
    if(bs != NULL && bs->bitmap != NULL){
        bitmap_destroy(bs->bitmap); //destroy bitmap then free memory
        free(bs);
        return;
    }
}

size_t block_store_allocate(block_store_t *const bs){
    if(bs == NULL) return SIZE_MAX;

    size_t fzAddress = bitmap_ffz(bs->bitmap); //find first zero
    if (fzAddress == SIZE_MAX || fzAddress == block_size-1) return SIZE_MAX;

    bitmap_set(bs->bitmap, fzAddress); //set first zero
    return fzAddress;
}


bool block_store_request(block_store_t *const bs, const size_t block_id){
    if(bs == NULL || block_id > block_size-1) return 0;

    if(bitmap_test(bs->bitmap, block_id) == 1) return 0; //if the bit is set, terminate

    bitmap_set(bs->bitmap, block_id);

    if(bitmap_test(bs->bitmap, block_id) == 0) return 0; //if the bit is not set, terminate

    return 1;

}

void block_store_release(block_store_t *const bs, const size_t block_id){
    if(bs != NULL) bitmap_reset(bs->bitmap, block_id);
}

size_t block_store_get_used_blocks(const block_store_t *const bs){
    if(bs != NULL) return bitmap_total_set(bs->bitmap); //return total set bits

    return SIZE_MAX; //default condition for errors
}

size_t block_store_get_free_blocks(const block_store_t *const bs){
    if(bs != NULL) return (block_size-1)-bitmap_total_set(bs->bitmap); //free blocks is available blocks subtracted by used blocks
    
    return SIZE_MAX; //default condition for errors
}

size_t block_store_get_total_blocks(){
    return block_size-1; //available blocks = n-1
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer){
    if(bs == NULL || block_id > block_size-1 || buffer == NULL) return 0;
    memcpy(buffer, bs->data[block_id],block_size); //copy block id into buffer
    return block_size;
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer){
    if(bs == NULL || buffer == NULL) return 0;
    memcpy(bs->data[block_id], buffer, block_size); //copy buffer into block id
    return block_size;
}

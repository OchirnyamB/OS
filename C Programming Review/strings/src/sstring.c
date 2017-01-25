#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/sstring.h"

bool string_valid(const char *str, const size_t length) {

    if(str == NULL || length == 0) return false;

    if(str[length-1] == '\0') return true;
    
	return false;
}

char *string_duplicate(const char *str, const size_t length) {

    if(str == NULL || length == 0) return NULL;
    else {
        char * new_str = malloc(sizeof(char) * length);
        return strncpy(new_str, str, length);
    }

	return NULL;

}

bool string_equal(const char *str_a, const char *str_b, const size_t length) {

	if (str_a == NULL || str_b == NULL || length == 0) return false;
    
    if(!strcmp(str_a, str_b)) return true;

    return false;
}

int string_length(const char *str, const size_t length) {

    if(str == NULL || length == 0) return -1;
    return strlen(str);
}

int string_tokenize(const char *str, const char *delims, const size_t str_length,char **tokens, const size_t max_token_length, const size_t requested_tokens) {

    if(str == NULL || delims == NULL || str_length == 0 || tokens == NULL || requested_tokens == 0 || max_token_length == 0) return 0; 

    for(int i = 0; i < requested_tokens; i++){
        if(tokens[i] == NULL) return -1; 
    }
    

    char* src = malloc(sizeof(char)*str_length);
    //memset(src, '\0', sizeof(src));
    strcpy(src, str);

    printf("%s", src);
    char* token = malloc(sizeof(char)*max_token_length);
    //token = strtok(src, delims);
   /* int i = 0;
    strcpy(*(tokens+i), token);
    printf("%s", (tokens);*/
    //i++;
    
    /*while(token != NULL){
        token = strtok(NULL, delims);
        strcpy(*(tokens+i), token);
      //  i++;
    }*/

    /*int i =0;
    char* token;
    token = strtok(src, delims);
    strcpy(*(tokens+i), token);
    
    while(token != NULL){
        token = strtok(NULL, delims);
        strcpy(*(tokens+i), token);
        i++;
    }

    while(*tokens != NULL){
        *(tokens+i) = (strtok(str, delims));
        i++;
    }*/
    free(token);
	return 1;
}

bool string_to_int(const char *str, int *converted_value) {

    if(str == NULL || converted_value == NULL) return false;

    if(atoi(str) == -1) return false;
    
    else *converted_value = atoi(str);

	return true;
}

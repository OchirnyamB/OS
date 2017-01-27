#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/sstring.h"

bool string_valid(const char *str, const size_t length) {

    if(str == NULL || length == 0) return false;

    /* A string is null terminated if the last character is the null terminator.
     * Since array indexes are 0-based, we compare length -1 to a literal null terminator.
     */
    if(str[length-1] == '\0') return true;
    
	return false;
}

char *string_duplicate(const char *str, const size_t length) {

    if(str == NULL || length == 0) return NULL;
    else {
        char * new_str = malloc(sizeof(char) * length); //Malloc new string
        return strncpy(new_str, str, length); //Copy and return new string
    }

	return NULL;

}

bool string_equal(const char *str_a, const char *str_b, const size_t length) {

	if (str_a == NULL || str_b == NULL || length == 0) return false;
    
    /*
     * strcmp return 0 if both parameters are equal.
     * By checking if stcmp is negated, we are checking if the value returned by the function is 0.
     */
    if(!strcmp(str_a, str_b)) return true;

    return false;
}

int string_length(const char *str, const size_t length) {

    if(str == NULL || length == 0) return -1;
    return strlen(str);
}

int string_tokenize(const char *str, const char *delims, const size_t str_length,char **tokens, const size_t max_token_length, const size_t requested_tokens) {

    if(str == NULL || delims == NULL || str_length == 0 || tokens == NULL || requested_tokens == 0 || max_token_length == 0) return 0; 

    /*
     * Here, I iterate through the tokens and check if any value is set to null.
     * If so, we have invalid input.
     */
    for(int i = 0; i < requested_tokens; i++){
        if(tokens[i] == NULL) return -1; 
    }
    
    char* str_cpy = malloc(sizeof(str)); //Create new array to copy the original becuase strtok won't accept a const char*.
    strncpy(str_cpy, str, str_length);

    char* token;

    token = strtok(str_cpy, delims); //First token
    int length = 0;
    strcpy(tokens[0], token); //Copy the first token into the first index of the output
    while(length < requested_tokens-1){
        length++;
        token = strtok(NULL, delims); //Go to the next token
        strcpy(tokens[length], token);
    }

    free(str_cpy);
    return requested_tokens;
}

bool string_to_int(const char *str, int *converted_value) {

    if(str == NULL || converted_value == NULL) return false;

    if(atoi(str) == -1) return false; //If atoi returns -1, the function has failed.
    
    else *converted_value = atoi(str);

	return true;
}

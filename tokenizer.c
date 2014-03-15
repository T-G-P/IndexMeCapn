/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

#define MAX_HEX_CHARS 2
#define MAX_OCT_CHARS 3
/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 *
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *fileName) {

    /*
     * Description: creates a new tokenizer struct from the token stream and delimiters
     * Parameters: set of delimiters, token stream
     * Modifies: nothing
     * Returns: a pointer to a tokenizer struct on success, a null pointer on failure
     *
     */

    if(fileName == NULL){
        return NULL;
    }


    /*convert file to string*/
    long fileSize;										//size of the file in chars
    char* str;											//the file in string form
    FILE* fp = fopen(fileName, "rb");					//open the file to read

    if(!fp){
        return NULL;
    }


    fseek(fp, 0, SEEK_END);								//move fp to 0 away from the end of the file
    fileSize = ftell(fp);								//get the size of the file by getting the current value of fp's position, which should be at EOF
    fseek(fp, 0, SEEK_SET);								//move fp to 0 away from the start of the file
    str = malloc(sizeof(char)*fileSize);				//allocate space for the file as a string based on the fileSize
    fread(str, 1, fileSize, fp);						//populate string with file info
    fclose(fp);

    TokenizerT* tokenizer = (TokenizerT*)malloc(sizeof(TokenizerT));

    if(tokenizer == NULL){
        return NULL;
    }

    tokenizer->copied_string = str;
    tokenizer->current_position = tokenizer->copied_string;

    return tokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {

    /*
     * Description: destroys tokenizer struct and deallocates all memory
     * Parameters: tokenizer to be destroyed
     * Modifies: tokenizer struct: deallocates memory
     * Returns: nothing
     */

    free(tk->copied_string);
    free(tk);

    return;
}

char is_delimiter(char character){

    /*
     * Description: determines if a particular character is a member of the set of delimiters
     * Parameters: character to be compared, string of delimiters
     * Modifies: Nothing
     * Returns: 1 if character is a delimiter, 0 if it is not
     */
    if(isalnum(character)) {
        return 0;
    }else{
        return 1;
    }
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {

    /*
     * Description: returns the next token from the token stream specified within the tokenizer
     * Parameters: tokenizer from which to extract token
     * Modifies: tokenizer->current_position: identifies starting point of next token; creates a new string with
     * Returns: token extracted as a char* on success, null on failure/end of string;
     */

    char* token = NULL;
    char* token_start = NULL;

    while(tk->current_position - tk->copied_string < strlen(tk->copied_string)) {
        if(!is_delimiter(*tk->current_position)) {

            token_start = tk->current_position;
            break;
        }
        tk->current_position++;
    }

    if(token_start == NULL) {
        return NULL;
    }

    while(tk->current_position - tk->copied_string < strlen(tk->copied_string)) {
        if(is_delimiter(*tk->current_position)) {
            break;
        }
        tk->current_position++;
    }

    token = (char*)malloc(sizeof(char) * (tk->current_position - token_start + 1));
    strncpy(token, token_start, tk->current_position - token_start);
    token[(tk->current_position - token_start)] = '\0';
    return token;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int tokenize(char *pathName, char *fileName ) {
    /*make sure there is a fileName*/
    if(!pathName){
        return 1;
    }

    /*create tokenizer*/
    TokenizerT* tokenizer = TKCreate(pathName);

    /*make sure TKCreate succeeds*/
    if(tokenizer == NULL) {
        return 1;
    }
    /*go through the tokens and add to data structure (to be added)*/
    char* token = NULL;
    while((token = TKGetNextToken(tokenizer)) != NULL) {
        struct Node* fileNode = createNode(fileName, token);
        add_node(fileNode, token);
        //printf("%s\n", token);
        sort_by_token();
    }

    /*free malloced data*/
    TKDestroy(tokenizer);
    return 0;
}

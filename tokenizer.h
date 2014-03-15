#ifndef TOKENIZER_H
#define TOKENIZER_H
/*
 * tokenizer.h
 */

#include <stdlib.h>
#include "uthash.h"
#include "hashadd.h"
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char* copied_string;
	char* current_position;
};

typedef struct TokenizerT_ TokenizerT;

TokenizerT *TKCreate(char *);

void TKDestroy(TokenizerT *);

char is_delimiter(char);

char *TKGetNextToken(TokenizerT *);

int tokenize(char *, char*);

#endif

/*
 * sorted-list.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include	"sorted-list.h"
#include "uthash.h"
#include "tokenizer.h"


int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

//Destructor functions
void destroyBasicTypeAlloc(void *p){
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for allocated memory (malloc,calloc,etc.)
	free(p);
}

void destroyBasicTypeNoAlloc(void *p) {
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
	return;
}

int main(int argc,char** argv){


    if(argc !=2){
        return 1;
    }
    tokenize(argv[1]);
    return 0;
}


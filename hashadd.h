#ifndef HASHADD_H
#define HASHADD_H
/*
 * hashadd.h
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "uthash.h"

struct Node{
    char *token;
    char *fileName;
    int count;
    struct Node *next;
};

struct hash{
    char *token;          /* key */
    struct Node *file;
    UT_hash_handle hh;         /* makes this structure hashable */
};

struct Node *createNode(void*,void *);

void add_node(struct Node*, void*);

int token_compare(struct hash *, struct hash *);

void sort_by_token(void);

void sortList(struct Node*);

void print_files(char*);

/*WORK IN PROGRESS
void free_lst(struct Node*);

void free_all_hashes(void);
*/

#endif


#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */
#include "uthash.h"
#include "hashadd.h"

struct Node *createNode(void*fileName, void *token)
{
    struct Node *llNode = malloc(sizeof(struct Node)*10);
    llNode->token = token;
    llNode->fileName =  fileName;
    llNode->next = NULL;
    llNode->count = 0;
    return llNode;
}

struct hash *tokenHash = NULL;

void add_node(struct Node *fileNode, void *token){
    struct hash *h;
    int toAdd = 0;
    HASH_FIND_STR(tokenHash, token, h);
    if(h == NULL){
        h = (struct hash*)malloc(sizeof(struct hash));
        h->token  = token;
        h->file = fileNode;
        h->file->count = 1;
        HASH_ADD_STR(tokenHash, token, h); //add this hash node to the hash table
    }
    else{
        struct Node* ptr = h->file;
        while(ptr!= NULL){        //finding the file here so we can increment its count
            if(fileNode->fileName == ptr->fileName){
                h->file->count++;
                toAdd = 1;  //this file exists in the hash and we just incremented the counter
                break;
            }else{
                ptr = ptr->next;
            }
        }
        if(toAdd == 0){
            ptr = fileNode;
            ptr->count++;
            ptr->next = h->file;
            h->file = ptr;  //making the pointer the head of the linked list
        }
    }
}
int token_compare (struct hash *a, struct hash *b) {
    return strcmp(a->token,b->token);
}

void sort_by_token() {
    HASH_SORT(tokenHash, token_compare);
}

void sortList(struct Node *head){
    struct Node *ptr = NULL;
    struct Node *counter = NULL;

    for(ptr = head; ptr->next != NULL; ptr = ptr->next)
    {
        for(counter = ptr->next; counter != NULL; counter = counter->next)
        {
            if(ptr->count > counter->count)
            {
                int temp = ptr->count;
                char *tmp = ptr->fileName;
                ptr->count = counter->count;
                strcpy(counter->fileName,ptr->fileName);
                counter->count = temp;
                strcpy(tmp,ptr->fileName);
            }
        }
    }
}


void print_files(char* fileName) {
    struct hash *h;
    struct Node *ptr;
    FILE* fp = fopen(fileName, "w");
    for(h=tokenHash; h != NULL; h=(struct hash*)(h->hh.next)) {
        fprintf(fp,"<list> %s\n\n", h->token);  //print the token
        ptr = h->file;  //points to hash node
        sortList(ptr);
        while(ptr){     //while the pointer is not null
            fprintf(fp,"%s %d ", ptr->fileName, ptr->count); //then for each token print file names and count
            ptr = ptr->next;
        }
        fprintf(fp,"\n\n</list>\n\n");
    }
}


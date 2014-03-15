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
/*This sorting function swaps the file name and data rather than manipulating pointers. */
void sortList(struct Node *head){
    struct Node *ptr = NULL;
    struct Node *counter = NULL;

    for(ptr = head; ptr->next != NULL; ptr = ptr->next){
        for(counter = ptr->next; counter != NULL; counter = counter->next) {
            if(ptr->count < counter->count){    //the first pointer  data is less than the counter pointer
                int temp = ptr->count;  //store lesser values count in temp variable
                char *tmp = counter->fileName;  //why does this work?
                //strcpy(tmp,counter->fileName);  //store greater values filename in temp variable (why does this not work)
                ptr->count = counter->count;    //set the lesser value to have the higher count (swap counts)
                counter->fileName = ptr->fileName;  //why does this work?
                //strcpy(counter->fileName,ptr->fileName);    //copy the lesser value filename into the counter (why doesn't this work)
                counter->count = temp;  //set the greater value to have the lesser count (swap counts)
                ptr->fileName = tmp;
                //strcpy(ptr->fileName,tmp);  //copy the greater value into the pointer spot
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

/* frees a linked list*/
void free_list(struct Node* ptr)
{
    struct Node* temp;
    while (ptr){
        temp = ptr;
        ptr =  ptr->next;
        free(temp);
    }
}

/*frees all the hashes*/
void free_all_hashes(){
    struct hash *h, *tmp;
    HASH_ITER(hh, tokenHash, h, tmp) {
        free_list(h->file);
        HASH_DEL(tokenHash,h);  /* delete; tokenHash advances to next */
        free(h);            
    }

}


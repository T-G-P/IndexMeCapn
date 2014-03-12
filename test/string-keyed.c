#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */
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

struct Node *createNode(void*fileName, void *token)
{
    struct Node *llNode = malloc(sizeof(struct Node)*10);
    llNode->token = token;
    llNode->fileName =  fileName;
    llNode->next = NULL;
    llNode->count = 0;
    return llNode;
}

struct hash *testHash = NULL;

void add_node(struct Node *fileNode, void *token){
    struct hash *h;
    HASH_FIND_STR(testHash, token, h);
    if(h == NULL){
        h = (struct hash*)malloc(sizeof(struct hash));
        h->token  = token;
        h->file = fileNode;
        h->file->count = 1;
        HASH_ADD_STR(testHash, token, h);  /* id already in the hash? */
    }
    else{
        h->file->count++;
    }
}

void print_files() {
    struct hash *h;
    for(h=testHash; h != NULL; h=(struct hash*)(h->hh.next)) {
        printf("file name: %s\ntoken key:%s\ntoken count: ", h->file->fileName, h->token);
        printf("file count %d\n",h->file->count);
    }
}
int main(int argc, char *argv[]) {
    struct Node* file1 = createNode("file1","hello");
    struct Node* file2 = createNode("file2","world");
    struct Node* file3 = createNode("file3","I");
    struct Node* file4 = createNode("file4","Miss");
    struct Node* file5 = createNode("file4","Sleep");
    add_node(file1, file1->token);
    add_node(file1, file1->token); //if this key exists, it's count is incremented
    add_node(file2, file2->token);
    add_node(file3, file3->token);
    add_node(file4, file4->token); //same thing add dupe key and increment count
    add_node(file4, file4->token);
    add_node(file5, file5->token);
    print_files();

    return 0;
}

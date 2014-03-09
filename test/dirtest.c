
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "tokenizer.h"

int dirCrawl(char *);

int dirCrawl(char *whatever){
    DIR * dir;
    struct dirent *entry;   //contains name of file that pointing to
    extern int errno;
    if((dir = opendir(whatever)) == 0){
        printf("could not open...\n");
        //tokenize here on whatever if possible
        entry = readdir(dir);
        if(entry != 0){
            tokenize(entry->d_name);
        }

    }
    else{
        while((entry = readdir(dir)) != 0){
            if((strcmp(entry->d_name, ".") == 0) || strcmp(entry->d_name, "..") == 0){
                continue;
            }
            else{
                //printf("%s\n",entry->d_name);
                if(entry->d_type == DT_DIR){
                    printf("This is a directory %s\n", entry->d_name);
                    char *next_dir = malloc(strlen(whatever) + strlen(entry->d_name) + 1 + 1);
                    sprintf(next_dir, "%s/%s", whatever, entry->d_name);
                    dirCrawl(next_dir);
                    free(next_dir);
                }else if(entry->d_type == DT_REG){
                    printf("This is a file %s\n", entry->d_name);
                    //tokenize if possible
                    char *next_file = malloc(strlen(whatever) + strlen(entry->d_name) + 1 + 1);
                    sprintf(next_file, "%s/%s", whatever, entry->d_name);
                    tokenize(next_file);
                    free(next_file);

                }
            }
        }
        closedir(dir);
    }
    return 0;
}
int main(int argc, char** argv){
    /*
     * FILE* fp;
     fp = fopen(argv[1], "r");
     if(fp == NULL){
     }
     */
    dirCrawl(argv[1]);

}

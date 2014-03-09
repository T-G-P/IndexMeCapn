//ISDIR: Returns 1 if the string is a directory,
// 0 if it's a file,
// -1 otherwise
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int dirCrawl(char *);

int dirCrawl(char *whatever){
	DIR * dir;
	struct dirent *entry;   //contains name of file that pointing to
	extern int errno;
	if((dir = opendir(whatever)) == 0){
		printf("could not open...\n");
	}
	else{
		while((entry = readdir(dir)) != 0){
			if((strcmp(entry->d_name, ".") == 0) || strcmp(entry->d_name, "..") == 0){
				continue;
			}
			else{
				printf("%s\n",entry->d_name);
				if(entry->d_type == DT_DIR){
					char *next_dir = malloc(strlen(whatever) + strlen(entry->d_name) + 1 + 1);
					sprintf(next_dir, "%s/%s", whatever, entry->d_name);
					dirCrawl(next_dir);
					free(next_dir);
				}else if(entry->d_type == DT_REG){
					//tokenize if possible
				}
			}
		}
		closedir(dir);
	}
	return 0;
}
int main(int argc, char** argv){
	dirCrawl(argv[1]);

}

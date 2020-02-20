#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

#define PAT "/etc"

int main(void)
{
    DIR *dp;
    struct dirent *cur;

    dp = opendir(PAT);
    if(dp == NULL){
        perror("opendir()");
        exit(1);
    }

    while((cur = readdir(dp)) != NULL)
    {
        puts(cur->d_name);
    }

    closedir(dp);

    exit(0);
}

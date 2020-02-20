#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv)
{
    FILE *fp;
    char *linebuf;
    size_t linsize;

    if(argc < 2)
    {
        fprintf(stderr,"Usage...\n");
        exit(1);
    }

    fp = fopen(argv[1],"r");
    if(fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    /*!!!!!!!!!!!!!!!!!!!!!!*/
    linebuf = NULL;
    linsize = 0;

    while(1)
    {
        if(getline(&linebuf,&linsize,fp) < 0)
            break;
        printf("%d\n",strlen(linebuf));
        printf("%d\n",linsize);
    }

    fclose(fp);
    //free(linebuf);//new delete 也可以申请空间
    exit(0);
}
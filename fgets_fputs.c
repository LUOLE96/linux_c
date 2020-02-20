#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc,char **argv)
{
    FILE *fps,*fpd;
    int ch;
    char buf[BUFSIZE] = {0};

    if(argc < 3)
    {
        fprintf(stderr,"usage : %s <src_file> <des_file>\n",argv[0]);
        exit(1);
    }

    fps = fopen(argv[1],"r");
    if(fps == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    fpd = fopen(argv[2],"w");
    if(fpd == NULL)
    {
        fclose(fps);
        perror("fopen()");
        exit(1);
    }

    while(fgets(buf,BUFSIZE,fps) != NULL)
        fputs(buf,fpd);

    fclose(fpd);
    fclose(fps);

    exit(0);
}
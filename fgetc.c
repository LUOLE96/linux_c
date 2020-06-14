#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    FILE *fps;
    int count = 0;

    fps = fopen(argv[1],"r");
    if(fps == NULL){
        perror("fopen()");
        exit(1);
    }

    while(fgetc(fps) != EOF){
        count++;
    }
    printf("count = %d\n",count);

    fclose(fps);

    exit(0);
}
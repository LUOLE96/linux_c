#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    char str[60];

    fp = fopen("test.txt","r");
    if(NULL == fp){
        perror("fopen error");
        exit(1);
    }

    //char buf[128] = "";
    char *buf = malloc(128);
    fgets(buf,sizeof(buf),fp);
    buf[strlen(buf) - 1] = 0; //去除尾部换行
    printf("buf = %s\n",buf);

    fclose(fp);
    free(buf);
    buf = NULL;

    exit(0);
}
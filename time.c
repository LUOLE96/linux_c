#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define FNAME "/tmp/out"
#define BUFSIZE 1024

int main(void)
{
    FILE *fp;
    int count = 0;
    time_t stamp;
    struct tm *tm;
    char buf[BUFSIZE];
    fp = fopen(FNAME,"a+");
    if(fp == NULL){
        perror("fopen()");
        exit(1);
    }

    while(fgets(buf,BUFSIZ,fp) != NULL)
        count++;

    while(1)
    {
        time(&stamp);
        tm = localtime(&stamp);
        fprintf(fp,"%-4d%d-%d-%d %d:%d:%d\n",++count,\
                tm->tm_year + 1900,tm->tm_mon + 1,tm->tm_mday,\
                tm->tm_hour,tm->tm_min,tm->tm_sec);

        fflush(fp);
        sleep(1);//可控的动态内存泄漏
    }

    fclose(fp);

    exit(0);
}
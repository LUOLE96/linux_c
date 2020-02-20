#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    
#include <unistd.h>

int main(void)
{
    FILE *fp = fopen("test.txt","w+");
    if(NULL == fp)
    {
        perror("fopen file error");
        return -1;
    }

    const char *str = "hello world\n";
    while(*str != 0)
        fputc(*str++,fp);

    rewind(fp);

    char ch = 0;
    while((ch = fgetc(fp)) != EOF)
        putchar(ch);

    fclose(fp);
    exit(0);
}
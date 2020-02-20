#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char str[50];

    printf("please input a string\n");
    gets(str);

    puts(str);

    exit(0);
}
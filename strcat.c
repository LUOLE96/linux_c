#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *str;

    while(1){
        strcat(str,"a");
        printf("%s\n",str);
    }

    exit(0);
}
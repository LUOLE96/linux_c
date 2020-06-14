#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *dup_str,*string = "i am won";
    dup_str = strdup(string);
    printf("%s\n",dup_str);
    free(dup_str);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    puts(getenv("PATH"));
    getchar();

    exit(0);
}
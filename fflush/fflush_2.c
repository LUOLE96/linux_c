#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int a;
    char c;

    scanf("%d",&a);
    fflush(stdin);//没有起作用？？？？？
    c = getchar();

    printf("a = %d,c = %c",a,c);

    exit(0);
}
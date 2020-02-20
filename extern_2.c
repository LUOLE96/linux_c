#include <stdio.h>

extern fun();

int main(void)
{
   // extern i = 12;//error
    extern double i;//结果不正确waring

    i = 12;//true

    printf("%d\n",i);
    
    fun();

    return 0;
}
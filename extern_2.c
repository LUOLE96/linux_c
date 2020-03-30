#include <stdio.h>

extern int fun();

int main(void)
{
   // extern i = 12;//error
    extern double i;//结果不正确waring
    //extern int i;

    i = 12;//true

    printf("%d\n",i);
    
    fun();

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    alarm(10);
    alarm(1);
    alarm(5);//最后一个有效

    while(1)
        pause();

    exit(0);
}
#include <stdio.h>
#include <stdlib.h>

/*
缓冲区的作用 ： 大多数情况下是好事，合并系统调用
行缓冲：换行时候刷新，满了刷新，强制刷新（标准输出是这样的，因为是终端设备）
全缓冲：满了刷新，强制刷新（默认，只要不是终端设备）
无缓冲：如stderr,需要立即输出的内容
*/

int main(void)
{
    int i;

    printf("before while()");
    fflush(stdout);

    while(1);

    printf("after while()");
    fflush(NULL);//刷新所有


    exit(0);
}
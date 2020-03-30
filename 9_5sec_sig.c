#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//static int loop = 1;//该程序加-O1优化编译选项后，程序结果死循环
static volatile int loop = 1;//该程序加-O1优化编译选项后，程序结果死循环

static void alrm_handler(int s)
{
    loop = 0;
}

int main(void)
{
    int64_t count = 0;

    signal(SIGALRM,alrm_handler);
    alarm(5);
    

    while(loop)
        count++;
    
    printf("%lld\n",count);

    exit(0);
}
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigfun(int signo)
{
    if(SIGINT == signo){
        printf("signal is SIGINT\n");
    }
    else if(SIGQUIT == signo){
        printf("signal is SIGQUIT\n");
    }
}

int main(void)
{
    signal(SIGINT,sigfun);
    signal(SIGQUIT,sigfun);

    sigset_t bset = {0},pset = {0};
    sigaddset(&bset,SIGINT);
    sigaddset(&bset,SIGQUIT);

    printf("SIG_BLOCK\n");
    if(sigprocmask(SIG_BLOCK,&bset,NULL) < 0){
        perror("sigprocmask error");
        return -1;
    }

    int i;
	for(i = 0; i < 10; i++)
	{
		printf("this is test\n");	//此时当SIGINT，SIGQUIT信号产生时并不会立即进入信号处理函数，被屏蔽的信号进入阻塞信号集中
		sleep(1);
	}

    if(sigpending(&pset) < 0)	//获取屏蔽信号集
	{
		perror("sigpending error");
		return -1;
	}

	if(sigismember(&pset,SIGINT) > 0)	//查询屏蔽信号集中有没有指定信号,从而进行处理
	{
		printf("do some thing about SIGINT\n");
		sigfun(SIGINT);
		sigdelset(&pset,SIGINT);
	}

	for(i = 0; i < 10; i++)
	{
		printf("this is test\n");	//此时当SIGINT，SIGQUIT信号产生时并不会立即进入信号处理函数，被屏蔽的信号进入阻塞信号集中
		sleep(1);
	}
    
	if(sigismember(&pset,SIGQUIT) > 0)
	{
		printf("do some thing about SIGQUIT\n");
		sigfun(SIGQUIT);
		sigdelset(&pset,SIGQUIT);
	}
}


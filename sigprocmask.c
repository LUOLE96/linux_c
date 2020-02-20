#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigfun(int signo)
{
    if(SIGINT == signo)
        printf("signal is SIGINT\n");
    else if(SIGQUIT == signo)
        printf("signal is SIGQUIT\n");
}

int main(void)
{
    signal(SIGINT,sigfun);
    signal(SIGQUIT,sigfun);

    sigset_t bset = {0};
    sigaddset(&bset,SIGINT);
    sigaddset(&bset,SIGQUIT);

    printf("SIG_BLOCK\n");
    if(sigprocmask(SIG_BLOCK,&bset,NULL) < 0){
        perror("sigpromask error");
        return -1;
    }

    int i;
    for(i = 0;i < 10;i++){
        printf("this is test\n");
        sleep(1);
    }
	printf("SIG_UNBLOCK\n");
	if(sigprocmask(SIG_UNBLOCK,&bset,NULL) < 0)	//解屏蔽SIGINT，SIGQUIT后，系统自动从阻塞信号集中取出并响应同种信号1次
	{
		perror("sigprocmask error");
		return -1;
	}
    
    for(i = 0; i < 10; i++)
	{
		printf("this is test\n");
		sleep(1);
	}


}
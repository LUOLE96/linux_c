#include <signal.h>
#include <stdio.h>

int main(void)
{
    sigset_t set = {0};

    #if 0
	if(sigemptyset(&set) < 0)	//清空信号集
	{
		perror("sigemptyset error");
		return -1;
	}
#endif

#if 0
	if(sigfillset(&set) < 0)	//填充64种信号
	{
		perror("setfillset error");
		return -1;
	}
#endif


#if 1
	sigaddset(&set,SIGINT);		//添加指定信号到信号集
	sigaddset(&set,SIGQUIT);
#endif

	//sigdelset(&set,SIGINT);		//从信号集中删除指定信号

	if(sigismember(&set,SIGINT) > 0)	//从信号集中查询指定信号
		printf("have SIGINT\n");
	else
		printf("not SIGINT\n");

}
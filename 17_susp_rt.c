#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
//实时信号

#define MYRTSIG (SIGRTMIN+6)
static void MYSIG_handler(int s){
    write(1,"!",1);
}

int main(void)
{
    int i,j;
    sigset_t set,oset,saveset;
    //signal(SIGINT,SIG_IGN);//标准信号
    signal(MYRTSIG,MYSIG_handler);//信号是否排队，响应是否有顺序要求，取决你用什么信号，不取决于你用什么函数
    sigemptyset(&set);
    sigaddset(&set,MYRTSIG);
    sigprocmask(SIG_UNBLOCK,&set,&saveset);//保存进入模块之前的状态
    sigprocmask(SIG_BLOCK,&set,&oset);

    for(j = 0;j < 1000;j++){
        for(i = 0;i < 5;i++){
            write(1,"*",1);
            sleep(1);
        }
        write(1,"\n",1);

    sigsuspend(&oset);
    /*相当于sigsuspend的作用，但不是由他们封装。下面的操作不原子，实现不了预期功能
        sigset_t tmpset;
        sigprocmask(SIG_SETMASK,&oset,&tmpset);
        pause();
        sigprocmask(SIG_SETMASK,&tmpset,NULL);
    */
    }
    sigprocmask(SIG_SETMASK,&saveset,NULL);
    return 0;
}
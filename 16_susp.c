#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void int_handler(int s){
    write(1,"!",1);
}

int main(void)
{
    int i,j;
    sigset_t set,oset,saveset;
    //signal(SIGINT,SIG_IGN);
    signal(SIGINT,int_handler);
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
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
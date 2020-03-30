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

    for(j = 0;j < 1000;j++){
        sigprocmask(SIG_BLOCK,&set,&oset);
        for(i = 0;i < 5;i++){
            write(1,"*",1);
            sleep(1);
        }
        write(1,"\n",1);
        sigprocmask(SIG_SETMASK,&oset,NULL);
    }
    sigprocmask(SIG_SETMASK,&saveset,NULL);
    return 0;
}
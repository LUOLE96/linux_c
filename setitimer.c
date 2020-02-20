#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
//alarm():只会在指定时间后产生一个SIGLARM信号,闹钟
//setitmer():循环不停地产生SIGLARM信号,定时器

void sigfun(int signo)
{
    if(SIGALRM == signo){
        printf("SIGALRM is start\n");
    }
}

int main(void)
{
    signal(SIGALRM,sigfun);

    struct itimerval newtim = {0},oldtim = {0};
    newtim.it_interval.tv_sec = 1;//以后没一次
    newtim.it_interval.tv_usec = 0;
    newtim.it_value.tv_sec = 3;//第一次
    newtim.it_value.tv_usec = 0;

    if(setitimer(ITIMER_REAL,&newtim,&oldtim) < 0){
        perror("setitimer error");
        return -1;
    }

    int i;
    for(i = 0;i < 10;i++){
        printf("this is test\n");
        sleep(1);
    }

    setitimer(ITIMER_REAL,&oldtim,NULL);

}
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void sigfun(int signo)
{
    if(SIGIO == signo){
        char buf[128] = {0};
        int len = read(STDIN_FILENO,buf,sizeof(buf) - 1);
        printf("recv len = %d buf = %s\n",len,buf);
    }
}

int main(void)
{
    signal(SIGIO,sigfun);

    int oldflag = fcntl(STDIN_FILENO,F_GETFL);
    int newflag = oldflag | O_ASYNC;
    if(fcntl(STDIN_FILENO,F_SETFL,newflag) < 0){
        perror("fcntl() error");
        return -1;
    }

    if(fcntl(STDIN_FILENO,F_SETOWN,getpid()) < 0){
        perror("fcntl setown error");
        return -1;
    }

    int i;
    for(i = 0;i < 10;i++){
        printf("this is test\n");
        sleep(1);
    }

    if(fcntl(STDIN_FILENO,F_SETFL,newflag) < 0){
        perror("fcntl() error");
        return -1;
    }

}
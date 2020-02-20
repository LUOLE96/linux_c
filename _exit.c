#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void exit_fun(void)
{
    printf("%s : close or free\n",__FUNCTION__);
}

int main(void)
{
    pid_t pid = fork();
    if(pid < 0){
        perror("fork error");
        return -1;
    }
    else if(pid > 0){
        wait(NULL);
        printf("parent start\n");
        printf("parent over\n");
    }
    else if(0 == pid){
        atexit(exit_fun);
        printf("sub : open or malloc\n");

        //exit(0);
        _exit(0);
    }


    exit(0);
}
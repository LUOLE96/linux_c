#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200

int main(void)
{
    int i,j,mark;
    pid_t pid = 0;
    for(i = LEFT;i <= RIGHT;i++){

        pid = fork();
        if(pid < 0){
            perror("fork()");
            exit(1);
        }

        if(pid == 0){
                mark = 1;
                for(j = 2;j < i/2;j++){
                    if(i % j == 0){
                        mark = 0;
                        break;
                    }
                }
            if(mark)
                printf("%d is a primer\n",i);

             exit(0);//!!!!!!!!!!!!!!!
        }
    }
    
    int st;
    for(i = LEFT;i <= RIGHT;i++){
        //wait(&st);//st 保存子进程退出的状态
        wait(NULL);
    }
    exit(0);
}
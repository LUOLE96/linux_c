#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//永远不要猜测假设父子进程谁先运行
int main(void)
{
    pid_t pid;
    printf("[%d]:begin\n",getpid());//输出设备行缓冲模式。\n刷新缓冲区  写文件全缓冲模式，\n只是换行

    fflush(NULL);//!!!!!!!!!!!

    pid = fork();
    if(pid < 0){
        perror("fork()");
        exit(0);
    }

    if(pid == 0){//child
        printf("[%d]:child is working\n",getpid());
    }
    else
    {
        printf("[%d]:parent is working\n",getpid());
    }
    
    printf("[%d]:end!\n",getpid());
    getchar();
    exit(0);
}
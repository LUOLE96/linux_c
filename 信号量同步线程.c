//下面以一个简单的多线程例子说明如何使用信号量进行线程同步。
//在主线程中，创建一个子线程用于处理 resource 共享资源，如果主线程有需求（sem_post），就往其后追加一个 ‘a’ 字符串。
//调试没有完成
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

sem_t sem;

void *change_resource(void *res)
{
    char *msg;

    while(1){
        sem_wait(&sem);
        strcat(msg,"a");
        printf("resource changed with value: %s\n", msg);
    }
}

int main(void)
{
    pthread_t thread;
    char *res;
    int ret = sem_init(&sem,0,0);
    if(ret < 0){
        printf("ssem_init failed\n");
        exit(1);
    }

    ret = pthread_create(&thread,NULL,change_resource,(void *)res);
    if(ret != 0){
        perror("pthread_create failed\n");
        exit(1);
    }

    while(1){
        sem_post(&sem);
        //printf("%s",res);
        sleep(1);
    }

    exit(0);
}
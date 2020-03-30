#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static void *func(void *p)
{
    puts("thread is working!");
    //return NULL;
    pthread_exit(NULL);//实现线程的清理
}

int main(void)
{
    pthread_t tid;
    int err;

    puts("Begin!");
    err = pthread_create(&tid,NULL,&func,NULL);
    if(err){
        fprintf(stderr,"pthread_create():%s\n",strerror(err));
        exit(1);
    }

    pthread_join(tid,NULL);
    puts("end!");

    exit(0);
}
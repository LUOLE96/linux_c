#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
//没有规律，取决于调度器的调度策略
#define THRNUM 4

static void *thr_func(void *p){
    int c = 'a' + (int)p;

    while(1)
        write(1,&c,1);
    
    pthread_exit(NULL);
}

int main(void)
{
    int i,err;
    pthread_t tid[THRNUM];

    for(i = 0;i < THRNUM;i++){
        err = pthread_create(tid + i,NULL,thr_func,(void *)i);
        if(err){
            fprintf(stderr,"pthread_create():%s\n",strerror(err));
            exit(1);
        }
    }

    alarm(6);

    for(i = 0;i < THRNUM;i++){
        pthread_join(tid[i],NULL);
    }

    exit(0);
}
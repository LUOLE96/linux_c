#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "mysem.h"
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT - LEFT + 1)
#define N 4
//程序有问题，没有实现效果
static void *thr_prime(void *p);
static mysem_t *sem;

int main(void)
{
    int i,err;
    pthread_t tid[THRNUM];

    sem = mysem_init(N);
    if(sem == NULL)
    {
        fprintf(stderr,"mysem_init() failed!");
        exit(1);
    }

    for(i = LEFT;i <= RIGHT;i++){
        mysem_sub(sem,1);
        err = pthread_create(tid+(i - LEFT),NULL,thr_prime,(void *)i);
        if(err){
            fprintf(stderr,"pthread_create():%s\n",strerror(err));
            exit(1);//应该考虑到已经创建成功的线程，应该先收回来，再推出，这里笼统处理
        }
    }

    for(i = LEFT;i <= RIGHT;i++)
        pthread_join(tid[i - LEFT],NULL);

    mysem_destroy(&sem);
    exit(0);
}

static void *thr_prime(void *p)
{
        int i,j,mark;
        //i = *(int *)p;//竞争
        i = (int)p;

        mark = 1;
        for(j = 2;j < i/2;j++){
            if(i % j == 0){
                mark = 0;
                break;
            }
        }
    if(mark)
        printf("%d is a primer\n",i);
    sleep(5);

    mysem_add(&sem,1);
    pthread_exit(NULL);
}
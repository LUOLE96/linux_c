#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 4

static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_num = PTHREAD_COND_INITIALIZER;

static void *thr_prime(void *p);

int main(void)
{
    int i,err;
    pthread_t tid[THRNUM];

    for(i = 0;i < THRNUM;i++){
        err = pthread_create(tid+i,NULL,thr_prime,(void *)i);
        if(err){
            fprintf(stderr,"pthread_create():%s\n",strerror(err));
            exit(1);//应该考虑到已经创建成功的线程，应该先收回来，再推出，这里笼统处理
        }
    }

    for(i = LEFT;i <= RIGHT;i++){
        pthread_mutex_lock(&mut_num);
        
        while(num != 0){//忙等，一直在枷锁，查看，造成cpu占用
            // pthread_mutex_unlock(&mut_num);
            // sched_yield();//出让调度器给别的线程，不会造成线程颠簸，达到sleep()的效果
            // pthread_mutex_lock(&mut_num);
            pthread_cond_wait(&cond_num,&mut_num);
        }
        num = i;
        pthread_cond_signal(&cond_num);
        pthread_mutex_unlock(&mut_num);
    }

    pthread_mutex_lock(&mut_num);
    while(num != 0){//防止主线程自己把最后一次任务给覆盖
        pthread_mutex_unlock(&mut_num);
        sched_yield();
        pthread_mutex_lock(&mut_num);
    }
    num = -1;
    pthread_cond_broadcast(&cond_num);
    pthread_mutex_unlock(&mut_num);

    for(i = LEFT;i < THRNUM;i++)
        pthread_join(tid[i],NULL);

    pthread_mutex_destroy(&mut_num);
    pthread_cond_destroy(&cond_num);

    exit(0);
}

static void *thr_prime(void *p)
{
        int i,j,mark;
        //i = *(int *)p;//竞争

    while(1){
        pthread_mutex_lock(&mut_num);
        while(num == 0){//忙等，一直在枷锁，查看，造成cpu占用
            // pthread_mutex_unlock(&mut_num);
            // sched_yield();
            // pthread_mutex_lock(&mut_num);
            pthread_cond_wait(&cond_num,&mut_num);
        }
        if(num == -1){
            pthread_mutex_unlock(&mut_num);
            break;
        }
        i = num;
        num = 0;
        pthread_cond_broadcast(&cond_num);
        pthread_mutex_unlock(&mut_num);

        mark = 1;
        for(j = 2;j < i/2;j++){
            if(i % j == 0){
                mark = 0;
                break;
            }
        }
        if(mark)
            printf("[%d]%d is a primer\n",(int)p,i);
    }
       
    pthread_exit(NULL);
}
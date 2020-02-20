#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static volatile int count = 0;
int haspro = 1;//控制条件
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *prouct_fun(void *args)
{
    while(1)
    {
        if(haspro)//如果有产品，生产者线程等待
            pthread_cond_wait(&cond,&mutex);

        count++;
        printf("product thread %lu : count = %d\n",pthread_self(),count);
        haspro = 1;
        pthread_cond_signal(&cond);//生产后有产品，则向消费者线程发送信号
        sleep(1);
    }

    return NULL;
}

void *constum_fun(void *args)
{
    while(1)
    {
        if(!haspro)//如果没有产品，消费者线程等待
            pthread_cond_wait(&cond,&mutex);

        count--;
        printf("coustum thread %lu : count = %d\n",pthread_self(),count);
        haspro = 0;
        pthread_cond_signal(&cond);//消费后没有产品，则向生产者线程发送信号
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t tid1 = 0,tid2 = 0;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_create(&tid1,NULL,prouct_fun,NULL);
	pthread_create(&tid2,NULL,constum_fun,NULL);

    pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

    pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}
#include <stdio.h>
#include <pthread.h>

static volatile int count = 0;

void *product_fun(void *args)
{
    int i;
    for(i = 0;i < 5;i++)
    {
        count++;
        printf("product thread %lu:count = %d\n",pthread_self(),count);
    }
}

void *constum_fun(void *argc){
    int i = 0;
    for(i = 0;i < 5;i++)
    {
        count--;
        printf("constum thread %lu:count = %d\n",pthread_self(),count);
    }
}

int main(void)
{
    pthread_t tid1 = 0,tid2 = 0;
    pthread_create(&tid1,NULL,product_fun,NULL);
    pthread_create(&tid2,NULL,constum_fun,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
}
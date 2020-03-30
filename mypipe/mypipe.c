#include <stdio.h>
#include <stdlib.h>
#include "mypipe.h"
#include <pthread.h>
//视频没有了，所以没有完成
struct mypipe_st
{
    int head;
    int tail;
    char data[PIPESIZE];
    int datasize;
    int count_rd;
    int count_wr;
    pthread_mutex_t mut;
    pthread_cond_t cond;
};

mypipe_t *mypipe_init(void)
{
    struct mypipe_st *me;
    
    me = malloc(sizeof(*me));
    if(me == NULL)
        return NULL;

    me->head = 0;
    me->tail = 0;
    me->datasize = 0;
    me->count_rd = 0;
    me->count_wr = 0;
    pthread_mutex_init(&me->mut,NULL);
    pthread_cond_init(&me->cond,NULL);

    return me;
}

static int mypipe_readbyte_unlocked(struct mypipe_st *me,char *datap)
{
    if(me->datasize <= 0)
        return -1;
    *datap = me->data[me->head];
    me->datasize--;
    return 0;
}

int mypipe_read(mypipe_t *ptr,void *buf,size_t count)
{
    int i;
    struct mypipe_st *me = ptr;

    pthread_mutex_lock(&me->mut);

    while(me->datasize <= 0 && me->count_wr > 0)
        pthread_cond_wait(&me->cond,&me->mut);
    
    if(me->datasize <= 0 && me->count_wr <= 0)
    {
        pthread_mutex_unlock(&me->mut);
        return 0;
    }

    for(i = 0;i < count;i++)
    {
        if(mypipe_readbyte(me,buf+i) != 0)
            break;
    }
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);

    return i;
}

/************************************************************
 * 函数功能：往ptr管道写count个buf里面的字节，没有完成
 * 函数参数：ptr管道，buf代写的缓冲区，count要写的字节数
 * 返回值：成功写入的字节数
 * **********************************************************/
int mypipe_write(mypipe_t *ptr,const void *buf,size_t count)
{
    int i;
    struct mypipe_st *me = ptr;

    pthread_mutex_lock(&me->mut);

    while(me->datasize >= PIPESIZE && me->count_rd > 0)
        pthread_cond_wait(&me->cond,&me->mut);
    
    if(me->datasize >= PIPESIZE && me->count_rd <= 0)
    {
        pthread_mutex_unlock(&me->mut);
        return 0;
    }

    for(i = 0;i < count;i++)
    {
        if(mypipe_readbyte(me,buf+i) != 0)
            break;
    }
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);

    return i;
}

int mypipe_destroy(mypipe_t *ptr)
{
    struct mypipe_st *me = ptr;

    pthread_mutex_destroy(&me->mut);
    pthread_cond_destroy(&me->cond);

    free(ptr);
    return 0;
}

int mypipe_register(mypipe_t *ptr,int opmap)
{
    /*if error*/
    //mypipe_t *me = ptr; 
    pthread_mutex_lock(&me->mut);
    if(opmap & MYPIPE_READ)
        me->count_rd++;
    if(opmap & MYPIPE_WRITE)
        me->count_wr++;

    pthread_cond_broadcast(&me->cond);

    while(me->count_rd <= 0 || me->count_wr <= 0)
        pthread_cond_wait(&me->cond,&me->mut);

    pthread_mutex_unlock(&me->mut);
    return 0;
}

int mypipe_unregister(mypipe_t *,int opmap)
{
 /*if error*/
    //mypipe_t *me = ptr; 
    pthread_mutex_lock(&me->mut);
    if(opmap & MYPIPE_READ)
        me->count_rd--;
    if(opmap & MYPIPE_WRITE)
        me->count_wr--;

    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);
    return 0;
}
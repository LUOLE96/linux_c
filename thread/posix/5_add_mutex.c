#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
//互斥量
#define THRNUM 20
#define LINESIZE 1024
#define FNAME "/tmp/out"

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;//静态初始化

static void *thr_add(void *p)
{
    FILE *fp;
    char linebuf[LINESIZE];

    fp = fopen(FNAME,"r+");
    if(fp == NULL){
        perror("fopen()");
        exit(1);
    }
   
   pthread_mutex_lock(&mut);//锁住的是该段区域的代码
    fgets(linebuf,LINESIZE,fp);
    fseek(fp,0,SEEK_SET);
     sleep(1);
    fprintf(fp,"%d\n",atoi(linebuf) + 1);//全缓冲模式，同时操作的时候要用fflush确保写到文件中去了
    fclose(fp);
    pthread_mutex_unlock(&mut);

    pthread_exit(NULL);
}

int main(void)
{
    int err,i;
    pthread_t tid[THRNUM];

    for(i = 0;i < THRNUM;i++){
        
        err = pthread_create(tid + i,NULL,thr_add,NULL);
        if(err){
            fprintf(stderr,"pthread_create():%s\n",strerror(err));
            exit(1);
        }
    }
    
    for(i = 0;i < THRNUM;i++){
        pthread_join(tid[i],NULL);
    }

    pthread_mutex_destroy(&mut);
    exit(0);
}
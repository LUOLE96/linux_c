#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
//流控10个字节，程序效果没有达到
#define CPS 10
#define BUFSIZE CPS
#define BURST 100

static volatile sig_atomic_t token = 0;//保证token原子

static void alrm_handler(int s)
{
    alarm(1);
    token++;
    if(token > BURST){
        token = BURST;
    }
}

int main(int argc,char **argv)
{
    int sfd,dfd = 1;
    char buf[BUFSIZ] = "";
    int len,ret,pos;

    if(argc < 2)
    {
        fprintf(stderr,"usage....\n");
        exit(1);
    }

    signal(SIGALRM,alrm_handler);
    alarm(1);

    do
    {
        sfd = open(argv[1],O_RDONLY);
        if(sfd < 0){
            if(errno != EINTR){
                perror("open()");
                exit(1);
            }
        }
    } while (sfd < 0);
    
    while(1){
        while(token <= 0)pause();//pause避免cpu占用
        token--;

        while((len = read(sfd,buf,BUFSIZ)) < 0)
        {
            if(errno == EINTR)
                continue;//如果被信号打断，则会攒下token,在数据激增的时候能快速处理
            perror("read()");
            break;
        }
        if(len == 0)
            break;

        pos = 0;
        while(len > 0){
            ret = write(dfd,buf + pos,len);
            if(ret < 0){
                if(errno == EINTR)
                    continue;
                perror("write()");
                exit(1);
            }
            pos += ret;
            len -= ret;
        }
    }
    close(sfd);

    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "proto.h"
#include <string.h>
#include <unistd.h>

int main(int argc,char **argv)
{
    int sd;
    struct msg_st sbuf;
    struct sockaddr_in raddr;


    sd = socket(AF_INET,SOCK_DGRAM,0);
    if(sd < 0){
        perror("socket()");
        exit(1);
    }

    struct ip_mreqn mreq;

    inet_pton(AF_INET,MTROUP,&mreq.imr_multiaddr);
    inet_pton(AF_INET,"0.0.0.0",&mreq.imr_address);
    mreq.imr_ifindex = if_nametoindex("eth0");

    if(setsockopt(sd,IPPROTO_IP,IPV6_MULTICAST_IF,&mreq,sizeof(mreq)) < 0){
        perror("setsocketopt()");
        exit(1);
    }

    //bind();

    strcpy(sbuf.name,"Alan");
    sbuf.math = htonl(rand() % 100);
    sbuf.chinese = htonl(rand() % 100);

    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(atoi(RCVPORT));
    inet_pton(AF_INET,MTROUP,&raddr.sin_addr);

    if (sendto(sd,&sbuf,sizeof(sbuf),0,(void *)&raddr,sizeof(raddr)) < 0)
    {
        perror("sendto()");
        exit(1);
    }

    puts("ok!");
    
    close(sd);

    exit(0);
}
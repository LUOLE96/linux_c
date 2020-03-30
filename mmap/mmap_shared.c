//匿名内存映射 与 使用 /dev/zero 类型，都不需要真实的文件。
//要使用匿名映射之需要向 mmap 传入 MAP_ANON 标志，并且 fd 参数 置为 -1 。
//所谓匿名，指的是映射区并没有通过 fd 与 文件路径名相关联。匿名内存映射用在有血缘关系的进程间。

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct{
    char name[4];
    int age;
}people;

int main(int argc,char **argv)
{
    int i;
    people *p_map;
    char temp;
    p_map = (people *)mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);

    if(fork() == 0){
        sleep(2);
        for(i = 0;i < 5;i++)
            printf("child read : the %d people's age is %d,name is %s\n",i+1,(*(p_map + i)).age,(*(p_map + i)).name);
        (*p_map).age = 100;
        munmap(p_map,sizeof(people)*10);//实际上，进程终止时，会自动解除映射
        exit(0);
    }

    temp = 'a';
    for(i = 0;i < 5;i++){
        temp += 1;
        memcpy((*(p_map+i)).name,&temp,2);
        (*(p_map+i)).age = 20+i;
    }
    sleep(5);
    printf("parent read:the first people,s age is %d\n",(*p_map).age);
    printf("umap\n");
    munmap(p_map,sizeof(people)*10);
    printf("umap ok\n");
    
    return 0;
}

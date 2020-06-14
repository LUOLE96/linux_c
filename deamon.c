/*************************************************************************
    > File Name: deamon.c
    > Author: luole
    > Mail: 708920807@qq.com 
    > Created Time: 2020年05月16日 星期六 11时00分27秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PATH_MAX 128

int main(int argc,char *argv[])
{
	char strCurPath[PATH_MAX];
	if(daemon(1,1) < 0)
	{
		perror("error daemon..\n");
		exit(1);
	}
	sleep(10);
	if(getcwd(strCurPath,PATH_MAX) == NULL){
		perror("error getcwd");
		exit(1);
	}
	printf("%s\n",strCurPath);
	return 0;

}

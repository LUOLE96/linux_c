#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//系统环境变量 getenv()
//PATH HOME USER UID PWD SHELL
//成功与否 setenv(系统环境变量名，系统环境变量值，标志位)

int main(void)
{
	char *pathstr = getenv("PATH");
	printf("pathstr = %s\n",pathstr);

	char *userstr = getenv("USER");
	printf("userstr = %s\n",userstr);

    if(setenv("USER","root",1) < 0){
        perror("setenv error");
        return -1;
    }

    userstr = getenv("USER");
    printf("userstr = %s\n",userstr);
}
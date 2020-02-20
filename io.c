#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*标准io和文件io最好不要混用
文件Io是在标准io上进行二次封装
FILE ×fd-------int 

strace 命令可以跟踪可执行文件中的系统调用
*/

int main(void)
{
    putchar('a');
    write(1,"b",1);

    putchar('a');
    write(1,"b",1);

    putchar('a');
    write(1,"b",1);

    exit(0);
}
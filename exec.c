#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
*date + %s
*/
int main(void){
    puts("begin!");//./a.out > /tmp/out

    fflush(NULL);

    execl("/bin/date","date","+%s",NULL);//replace  pid相同
    perror("exec()");
    exit(1);

    puts("end!");
    exit(0);
}
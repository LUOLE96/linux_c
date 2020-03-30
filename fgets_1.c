#include <string.h>
#include <stdio.h>

int main(void)
{
    char buf[128] = "";
    //fgets(buf,sizeof(buf),stdin);//scanf,不接受\n
    scanf("%s",buf);
    buf[strlen(buf) - 1] = 0;

    fputs(buf,stdout);

    return 0;
}
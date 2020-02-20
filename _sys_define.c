#include <stdio.h>

//__FILE__:char *,当前宏所在文件名
//__func__:char *,当前宏所在函数名
//__LINE__:int:当前宏所在的行号
//__DATE__:char *:系统当前日期
//__TIME__:char *:系统当前时间

void test_fun(void)
{
    printf("%s %s %d\n",__FILE__,__func__,__LINE__);
}

int main(void)
{
    test_fun();
    printf("%s %s %d\n",__FILE__,__func__,__LINE__);
    printf("%s %s\n",__DATE__,__TIME__);

}
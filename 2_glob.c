#include <stdio.h>
#include <glob.h>

int main(void)
{
    glob_t buf;
    int i;

    glob("/dev/*",GLOB_NOSORT,NULL,&buf);

    for(i = 0;i < buf.gl_pathc;i++)
    {
        printf("buf.gl_pathv[%d] = %s\n",i,(buf.gl_pathv[i]));

    }

    globfree(&buf);

    return 0;
}
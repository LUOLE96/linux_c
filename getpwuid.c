#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int main(int argc,char **argv)
{
    struct passwd *pwline;

    if(argc < 2){
        fprintf(stderr,"usage...\n");
        exit(1);
    }

    pwline = getpwuid(atoi(argv[1]));

    puts(pwline->pw_name);

    exit(0);
}
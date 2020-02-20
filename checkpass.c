#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <string.h>
#include <crypt.h>
#include <unistd.h>

int main(int argc,char **argv)
{
    struct spwd *shadowline;
    char *input_pass,*crypted_pass;
    if(argc < 2)
    {
        fprintf(stderr,"usage....\n");
        exit(1);
    }

    input_pass = getpass("passward : ");

    shadowline = getspnam(argv[1]);

    crypted_pass = crypt(input_pass,shadowline->sp_pwdp);

    if(strcmp(shadowline->sp_pwdp,crypted_pass) == 0)
        puts("ok!");
    else
    {
        puts("fail!");
    }
    
    exit(0);
}
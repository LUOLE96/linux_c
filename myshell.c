#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DELIMS " \t\n"

struct cmd_st
{
    glob_t globres;
};

static void prompt(void)
{
    printf("mysh-0.1$");
}

static void parse(char *line,struct cmd_st *res)
{
    char *tok;
    int i = 0;

    while(1){
        tok = strsep(&line,DELIMS);
        if(tok == NULL)break;
        if(tok[0] == '\0')continue;

        glob(tok,GLOB_NOCHECK|GLOB_APPEND*i,NULL,&res->globres);
        i = 1;
    }

}

int main(void)
{
    struct cmd_st cmd;
    char *linebuf = NULL;
    size_t linebuf_size = 0;
    while(1){
        prompt();

        if(getline(&linebuf,&linebuf_size,stdin) < 0)
            break;

        parse(linebuf,&cmd);

        if(0){//是内部命令

        }
        else//是外部命令，/bin/。。。
        {
            pid_t pid = fork();
            if(pid < 0){
                perror("fork()");
                exit(1);
            }

            if(pid == 0){//child
                execvp(cmd.globres.gl_pathv[0],cmd.globres.gl_pathv);
                perror("execvp()");
                exit(1);
            }
            else//parent
            {
                wait(NULL);
            }
            

        }
        
    }


}
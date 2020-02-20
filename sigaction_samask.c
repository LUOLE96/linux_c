#include <stdio.h>
#include <signal.h>

int main(void)
{
    struct sigaction newact = {0};
    newact.sa_handler = NULL;
    newact.sa_flags = 0;

    sigaddset(&newact.sa_mask,SIGQUIT);
    sigaddset(&newact.sa_mask,SIGIO);

}
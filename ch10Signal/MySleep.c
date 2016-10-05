#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void sig_alrm(int signo)
{
    //do nothing...
}

unsigned int sleepl(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        return seconds;
    alarm(secondes);
    pause();
    return alarm(0);
}



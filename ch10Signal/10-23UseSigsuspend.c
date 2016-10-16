#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t quitflag;

static void sig_int(int signo)
{
    if (signo == SIGINT)
        printf("\ninterrupt\n");
    else if(signo == SIGQUIT)
        quitflag = 1;
}

int main(void)
{
    sigset_t newmask, oldmask, zeromask;

    if(signal(SIGINT, sig_int) == SIG_ERR)
       printf("signal (SIGINT) error!\n");
    if (signal(SIGQUIT, sig_int) == SIG_ERR)
        printf("signal(SIGIQUIT) error.\n");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    while(quitflag == 0)
        sigsuspend(&zeromask);
        //SIGQUIT 信号被捕获
    quitflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf("SIG_SETMASK error!\n");

    exit(0);
}

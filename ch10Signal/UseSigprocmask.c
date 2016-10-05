#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
        printf("Can't reset SIGQUIT\n");
}

int main()
{
    sigset_t newmask, oldmask, pendmask;
    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
        printf("Can't catch SIGQUIT.\n");

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        printf("SIG_BLOCK error\n");

    sleep(5);

    if (sigpending(&pendmask) < 0)
        printf("sigpending error\n");
    if (sigismember(&pendmask, SIGQUIT))
        printf("\nSIQGUIT pending\n");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf("SIG_SETMASK ERROR\n");
    printf("SIGQUIT unblocked \n");
    sleep(5);
    exit(0);
}

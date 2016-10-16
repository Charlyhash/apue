#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void pr_mask(const char* str)
{
    sigset_t sigset;
    int errno_save;

    errno_save = errno;     //保存的errno
    if (sigprocmask(0, NULL, &sigset) < 0)
    {
        printf("sigprocmask error!\n");
        exit(1);
    }
    else
    {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT))
            printf("SIGINT");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
         if (sigismember(&sigset, SIGUSR2))
            printf(" SIGUSR2");

        printf("\n");

    }
}

static void sig_int(int signo)
{
    pr_mask("\nin sig_int: ");
}

int main()
{
    sigset_t newmask, oldmask, waitmask;

    pr_mask("program start: ");

    if (signal(SIGINT, sig_int) == SIG_ERR)
        printf("signal(SIGINT) error.\n");
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    //Block SIGINT and save current signal mask.
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        printf("SIG_BLOCK ERROR.\n");

    pr_mask("in critical region: ");

    if (sigsuspend(&waitmask) != -1)
        printf("sigsuspend error.\n");

    pr_mask("after return from sigsuspend:");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf("SIG_SETMASK ERROR.\n");

    pr_mask("program exit: ");

    exit(0);
}

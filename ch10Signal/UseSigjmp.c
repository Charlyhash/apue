//信号屏蔽，sigsetjmp，siglongjmp实例
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>

static volatile sig_atomic_t canjump;
static sigjmp_buf jmpbuf;

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

    errno = errno_save;
    exit(0);
}

static void sig_usr1(int signo)
{
    time_t starttime;
    if (canjump == 0)
        return ;
    pr_mask("starting sig_usr1:");

    alarm(3);

    starttime = time(NULL);
    for (;;)
        if (time(NULL) > starttime + 5)
            break;
    pr_mask("finishing sig_usr1:");

    canjump = 0;
    siglongjmp(jmpbuf, 1);      //jump back to main, not return
}

static void sig_alrm(int signo)
{
    pr_mask("int sig_alrm: ");
}

int main()
{
    if (signal(SIGUSR1, sig_usr1) < 0)
        printf("signal (SIGUSR1) error\n");
    if (signal(SIGALRM,sig_alrm) < 0)
        printf("signal (SIGALRM) error\n");

    pr_mask("starting main: ");

    if (sigsetjmp(jmpbuf, 1))
    {
        pr_mask("ending main: ");
        exit(0);
    }
    canjump = 1;
    for (;;)
        pause();
}

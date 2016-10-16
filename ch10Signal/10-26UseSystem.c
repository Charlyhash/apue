#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sig_int(int sig_no)
{
    printf("caught SIGINT.\n");
}

static void sig_chld(int signo)
{
    printf("caught SIGCHLD\n");
}

int main()
{
    if (signal(SIGINT, sig_int) ==  SIG_ERR)
    {
        printf("signal(SIGINT) error.\n");
    }
    if (signal(SIGCHLD, sig_chld) == SIG_ERR)
        printf("signal(SIGCHLD) error.\n");
    if (system("/bin/ed") < 0)
        printf("system() error.\n");
    exit(0);

}

/*
 * 测试信号集
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main()
{
    sigset_t sigset;

    sigfillset(&sigset);    //填充所用信号

    if (sigismember(&sigset, SIGINT))
        printf("SIGINT exist int sigal set!\n");
    if (sigismember(&sigset,SIGTERM))
        printf("SIGTERM exits in signal_set!\n");
    if (sigismember(&sigset,SIGABRT))
        printf("SIGABRT exist in signal_set!\n");
    if (sigdelset(&sigset,SIGINT) < 0)
        perror("del error\n");
    else
        printf("SIGINT has been removed!\n");

    if (sigismember(&sigset,SIGINT))
        printf("SIGINT exist in signal_set!\n");
    else
        printf("SIGINT not exist in signal_set!\n");

    exit(0);
}

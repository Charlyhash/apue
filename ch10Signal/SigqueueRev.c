
//receive data use sigqueue()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sighandler(int signo, siginfo_t *info, void *ctx)
{
    //以下两种方式都能获得sigqueue发送的数据
    printf("receive the data by info->si_int: %d\n", info->si_int);
    printf("receive the data by info->si_value.sival_int:%d\n", info->si_value.sival_int);
}

int main()
{
    struct sigaction act;
    act.sa_sigaction = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;  //信号传递开关
    if (sigaction(SIGINT, &act, NULL) == -1)
    {
        perror("sigaction error!");
        exit(1);
    }
    for (;;)
    {
        printf("waiting a SIGINT signal...\n");
        pause();
    }
    return 0;
}

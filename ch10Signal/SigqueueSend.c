
//send datat use sigqueue()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage:%s pid\n", argv[0]);
        exit(1);
    }
    pid_t pid = atoi(argv[1]);
    sleep(2);
    union sigval mysigval;
    mysigval.sival_int = 100;
    printf("sending SIGINT signal to %d ......\n", pid);
    if (sigqueue(pid, SIGINT, mysigval) == -1)
    {
        perror("sigqueue error!");
        exit(1);
    }

    return 0;
}

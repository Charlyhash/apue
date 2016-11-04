#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        printf("fork error\n");
        exit(1);
    }
    else if (pid == 0)
    {
        if (execl("/home/ubuntu/Code/apue/ch8ForkContral/testinterp", "yan", "ke", (char*)0) < 0)
        {
            printf("execl error\n");
            exit(1);
        }
    }

    if (waitpid(pid, NULL, 0) < 0)
    {
        printf("waitpid error\n");
        exit(1);
    }

    exit(0);
}

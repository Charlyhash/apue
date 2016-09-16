#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globvar = 6;

int main()
{
    int var;
    pid_t pid;

    var = 88;
    printf("Befor fork\n");
    if ((pid = vfork()) < 0)
    {
        printf("Fork error\n");
        exit(1);
    }
    else if (pid == 0)
    {
        //子进程
        globvar++;
        var ++;
        _exit(0);
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}

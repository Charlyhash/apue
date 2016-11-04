#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

void ErrorExit(const char* m)
{
    perror(m);
    exit(EXIT_FAILURE);
}

void pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination,exit status = %d\n",\
                WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnoraml termination, signal = number = %d.\n",\
                WTERMSIG(status));
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n",\
                WSTOPSIG(status));
}

int main()
{
    pid_t pid;
    int status;

    if((pid = fork()) < 0)
        ErrorExit("fork error!");
    else if(pid == 0)
        exit(7);

    if (wait(&status) != pid)
        ErrorExit("wait error!");
    pr_exit(status);

    if ((pid = fork()) < 0)
        ErrorExit("fork error!");
    else if (pid == 0)
        abort();
    if (wait(&status) != pid)
        ErrorExit("wait error!");
    pr_exit(status);

    if ((pid = fork())<0)
        ErrorExit("wait error!");
    else if (pid == 0)
        status /= 0;
    if (wait(&status) != pid)
        ErrorExit("wait error!");
    pr_exit(status);

    exit(0);

}

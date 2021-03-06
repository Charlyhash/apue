#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int system(const char* cmdstring)
{
    pid_t pid;
    int status;
    struct sigaction ignore,saveintr,savequit;
    sigset_t chldmask, savemask;

    if (cmdstring == NULL)
        exit(1);
    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    if (sigaction(SIGINT, &ignore, &saveintr) < 0)
        exit(-1);
    if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
        exit(-1);
    sigemptyset(&chldmask);
    sigaddset(&chldmask, SIGCHLD);
    if (sigprocmask(SIG_BLOCK, &chldmask, &savemask))
        exit(-1);

    if ((pid = fork()) < 0)
    {
        status = -1;
    }
    else if (pid == 0)
    {
        sigaction(SIGINT, &saveintr, NULL);
        sigaction(SIGQUIT, &savequit, NULL);
        sigprocmask(SIG_SETMASK, &savemask, NULL);
        execl("/bin/sh", "sh", "-c", cmdstring, (char*)0);
        _exit(127);////子进程正常执行则不会执行此语句
    }
    else
    {
        while (waitpid(pid, &status, 0) < 0)
        {
            if (errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }

    if (sigaction(SIGINT, &saveintr, NULL)<0)
        exit(-1);
    if (sigaction(SIGQUIT, &savequit, NULL)<0)
        exit(-1);
    if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
        exit(-1);

    return (status);
}

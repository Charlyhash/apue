#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/stat.h>

#define ERR_EXIT(m)\
{\
    perror(m);\
    exit(EXIT_FAILURE);\
}\
while(0);\

int daemonize()
{
    int fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;

    umask(0);

    if ((pid = fork()) <0)
    {
        ERR_EXIT("fork error!");
    }
    else if (pid != 0)
        exit(0);

    setsid();

    if (chdir("/") < 0)
        ERR_EXIT("can't change director to /");
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        ERR_EXIT("can't get file limit.");
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (unsigned i = 0; i < rl.rlim_max; ++i)
        close(i);

    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    return 0;
}

int main()
{
    daemonize();
    openlog("daemotest", LOG_PID, LOG_USER);
    syslog(LOG_INFO, "program started.");
    while(1)
    {
        sleep(1);
    }

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define ERR_EXIT(m) \
do \
{\
  perror(m);\
  exit(EXIT_FAILURE);\
}\
while(0);\

void create_deamon(void);

int main()
{
    time_t t;
    int fd;
    create_deamon();
    while(1)
    {
        fd = open("deamon.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            ERR_EXIT("open error!");
        }
        t = time(0);
        char* buf = asctime(localtime(&t));
        write(fd, buf, strlen(buf));
        close(fd);
        sleep(60);
    }

    return 0;
}

void create_deamon()
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
        ERR_EXIT("fork error!");
    if (pid > 0)
        exit(EXIT_SUCCESS);
    if (setsid() == -1)
        ERR_EXIT("setsid() error");
    chdir("/");

    for (int i = 0; i < 3; ++i)
    {
        close(i);
        open("dev/null", O_RDWR);
        dup(0);
        dup(0);
    }
    umask(0);
    return;

}

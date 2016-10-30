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


int main()
{
    time_t t;
    int fd;
    if (daemon(0, 0) == -1)
        ERR_EXIT("daemon error!");
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

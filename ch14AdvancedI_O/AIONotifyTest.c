#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <aio.h>
#include <fcntl.h>

void AsyncRead(int s, siginfo_t* info, void* context)
{
    struct aiocb* ptr = (struct aiocb*)info->si_value.sival_ptr;
    printf("read = %s\n", (char*)ptr->aio_buf);
}

int main()
{
    struct aiocb cb;
    int fd;
    char sbuf[100];
    int ret;
    struct sigaction act;

    fd = open("aiotest.txt", O_RDWR, S_IRUSR|S_IWUSR);
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    act.sa_sigaction  = AsyncRead;
    sigaction(SIGIO, &act, NULL);

    bzero(&cb, sizeof(cb));
    cb.aio_fildes = fd;
    cb.aio_buf = sbuf;
    cb.aio_nbytes = 100;
    cb.aio_offset = 0;

    cb.aio_sigevent.sigev_value.sival_ptr = &cb;
    cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    cb.aio_sigevent.sigev_signo = SIGIO;

    ret = aio_read(&cb);
    if (ret == -1)
    {
        perror("aio_read error.");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i != 10)
    {
        printf("%d\n", i++);
        sleep(3);
    }

    return 0;

}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void Perror(const char* s)
{
    perror(s);
    exit(EXIT_FAILURE);
}

//check lock
pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    if (fcntl(fd, F_GETLK, &lock) < 0)
    {
            perror("fcntl error!");
            exit(EXIT_FAILURE);
        }

    if (lock.l_type == F_UNLCK)
    {
            return 0;
        }

    return (lock.l_pid);
}

//set lock or free lock
int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return (fcntl(fd, cmd, &lock));
}

int main()
{
    int fd = open("./test.tmp", O_WRONLY | O_CREAT | O_EXCL, 0777);
    if (fd == -1)
    {
        printf("file exit \n");
        fd = open("./test.tmp", O_WRONLY, 077);
    }
    else
        printf("create file success.\n");

    pid_t pid = getpid();
    printf("the proc pid:%d\n", pid);

    //check write
    pid_t lockpid = lock_test(fd, F_WRLCK, 0, SEEK_SET, 0);
    if (lockpid == 0)
        printf("check write lockable, ok\n");
    else
        printf("check write lockable, can't. \
                have read or write lock,ower pid : %d", lockpid);
    //set write lock
    if (lock_reg(fd, F_SETLK, F_WRLCK, 0, SEEK_SET, 0) < 0)
        printf("set write lock failed\n");
    else
        printf("set write lock success\n");
    sleep(60);
    return 0;
}

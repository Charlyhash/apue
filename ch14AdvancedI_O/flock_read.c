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
    //创建文件
    int fd = open("./test.tmp",O_RDONLY | O_CREAT | O_EXCL, 0777);
    if (fd == -1)
    {
        printf("file exit!\n");
        fd = open("./test.tmp", O_RDONLY, 0777);
    }
    else
        printf("create file success.\n");

    pid_t pid = getpid();
    printf("the proc pid : %d\n", pid);

    pid_t lockpid = lock_test(fd, F_RDLCK, 0, SEEK_SET, 0);
    if(lockpid == 0)
        printf("check read lockable, ok\n");
    else
        printf("check read lockable, can't.have write lock, owner pid : %d\n", lockpid);
    //set read lock
    if (lock_reg(fd, F_SETLK, F_RDLCK, 0,SEEK_SET, 0) < 0)
        printf("set read lock failed\n");
    else
        printf("set read lock success\n");

    sleep(60);
    return 0;

}

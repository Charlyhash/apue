#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main()
{
    umask(0);
    if (creat("foo", RWRWRW) < 0)
    {
        printf("creat foo error!\n");
        exit(1);
    }
    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (creat("bar", RWRWRW) < 0)
    {
        printf("creat bar error!\n");
        exit(1);
    }

    exit(0);
}

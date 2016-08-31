//test chmod

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


int main()
{
    struct stat statbuf;
    //
    if (stat("foo", &statbuf) < 0)
    {
        printf("stat error for foo\n");
        exit(1);
    }
    if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
    {
        printf("chmod error for foo\n");
        exit(1);
    }

    if (chmod("bar", S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH) < 0)
    {
        printf("chmod error for bar\n");
       exit(-1);
    }

    exit(0);
}

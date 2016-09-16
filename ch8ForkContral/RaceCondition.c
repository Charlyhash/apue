//模拟一个带有竞争条件的程序
#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>

static void charatatime(char*);

int main()
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        printf("fork error!\n");
        exit(1);
    }
    else if (pid == 0)
    {
        charatatime("output from child\n");
    }
    else
    {
        charatatime("output from parent\n");
    }

    exit(0);
}

static void charatatime(char* str)
{
    char* ptr;
    int c;
    setbuf(stdout, NULL);
    for (ptr = str;(c = *ptr++) != 0;)
        putc(c, stdout);
}

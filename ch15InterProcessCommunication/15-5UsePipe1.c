#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void ERR_EXIT(const char* m)
{
    perror(m);
    exit(EXIT_FAILURE);
}

int main()
{
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    if (pipe(fd) < 0)
        ERR_EXIT("pipe error!");

    if ((pid = fork))
}

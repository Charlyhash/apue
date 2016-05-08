/*************************************************************************
	> File Name: 1_7_mini_shell.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月08日 星期日 20时37分42秒
 ************************************************************************/

#include "apue.h"
#include <sys/wait.h>

int main()
{
    char buf[MAXLINE];
    pid_t pid;
    int status;
    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf)-1] == '\n')
            buf[strlen(buf) - 1] = 0;
        if ((pid = fork()) < 0)
        {
            err_sys("fork error");
        }
        else if (pid == 0)
        {
            execlp(buf, buf, (char*)0);
            err_ret("could not execute: %s", buf);
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }

    exit(0);
}

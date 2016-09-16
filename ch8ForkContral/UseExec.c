#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char* env_inti[] = {"USER=unknow", "PATH=/tmp", NULL};

int main()
{
    pid_t pid;
    if ((pid = fork()) < 0)
    {
        printf("fork error\n");
        exit(1);
    }
    else if(pid == 0)
    {
        if (execle("/home/ubuntu/Code/apue/ch8ForkContral/echoall", "echoall", "yan", "ke", "scut", (char*)0, env_inti) < 0)
        {
            printf("execle error\n");
            exit(1);
        }
     }

    if (waitpid(pid, NULL, 0) < 0)
    {
        printf("wait error!\n");
        exit(1);
    }
    else if (pid == 0)
    {
        if (execlp("echoall", "echoall", "only one arg", (char*)0) < 0)
        {
            printf("execlp error\n");
            exit(1);
        }
    }

    exit(0);
}

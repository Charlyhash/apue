#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define EXIT_ERR(m) \
{\
    perror(m);\
    exit(EXIT_FAILURE);\
}\
while (0);\

int main()
{
    int status;
    status = system("ls -l|wc -l");
    if (status == -1)
    {
            EXIT_ERR("system error");
    }
    else
    {
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status)==0)
                printf("run command successful\n");
            else
                printf("run command fail and exit code is %d\n", WEXITSTATUS(status));

        }
        else
        {
            printf("exit status = %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}

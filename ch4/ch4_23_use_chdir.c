#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    if (chdir("/tmp") < 0)
    {
        printf("chdir failed\n");
        exit(1);
    }
    printf("chdir to /tmp succeeded\n");
    exit(0);
}

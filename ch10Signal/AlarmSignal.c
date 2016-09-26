#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>

static void my_alarm(int signo)
{
    struct passwd* rootptr;

    printf("in signal handle\n");
    if ((rootptr = getpwnam("root")) == NULL )
    {
        printf("getpwnam(root) error\n");
    }

    alarm(1);

}


int main()
{
    struct passwd* ptr;

    signal(SIGALRM, my_alarm);
    alarm(1);
    for(;;)
    {
        if ((ptr = getpwnam("ubuntu")) == NULL)
            printf("getpwnam error\n");
        if (strcmp(ptr->pw_name, "ubuntu") != 0)
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
    }

    exit(0);
}

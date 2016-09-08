#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd* getpwnam(const char* name)
{
    struct passwd* ptr;
    setpwent();
    while ((ptr = getpwent()) != NULL)
    {
        if (strcmp(name, ptr->pw_name) == 0)
        {
            break;
        }
    }

    endpwent();
    return(ptr);
}

int main()
{
    struct passwd* p = getpwnam("yanke");
   if(p != NULL)
      printf("work direction : %s\n", p->pw_dir);

   exit(0);
}

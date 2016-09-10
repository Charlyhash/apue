#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BSZ 48

int main()
{
    FILE *fp;
    char buf[BSZ];

    memset(buf, 'a', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
    {
        printf("fmemopen error\n");
    }
    printf("initial buffer conternts : %s\n", buf);
    fprintf(fp, "hello, world");
    printf("before flush:%s\n", buf);
    fflush(fp);
    printf("after flush:%s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'b', BSZ-2);
    buf[BSZ-2] = '\n';
    buf[BSZ-1] = 'x';
    fprintf(fp, "hello, world");
    fclose(fp);
    printf("after fclose:%s\n", buf);
    printf("len of string int buf = %ld\n", (long)strlen(buf));

    return 0;
}

#include <stdio.h>
#include <setjmp.h>

static jmp_buf buf;

void second()
{
    printf("first!\n");
    longjmp(buf, 1);
}

void first()
{
    second();
    printf("first!\n");
}

int main()
{
    if (!setjmp(buf))
        first();
    else
        printf("main!\n");

    return 0;
}

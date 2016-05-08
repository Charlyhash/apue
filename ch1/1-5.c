/*************************************************************************
	> File Name: 1-5.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月08日 星期日 13时12分46秒
 ************************************************************************/

#include<stdio.h>
#include "apue.h"

int main()
{
    int c;
    while ((c = getc(stdin)) != EOF)
        if (putc(c, stdout) == EOF)
            err_sys("output error");

    if (ferror(stdin))
        err_sys("input error");

    exit(0);
}

/*************************************************************************
	> File Name: 1_8_print_error.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月08日 星期日 21时10分39秒
 ************************************************************************/

#include<stdio.h>
#include "apue.h"
#include <errno.h>

int main(int argc, char* argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    errno = ENOENT;
    perror(argv[0]);
    exit(0);
}

/*************************************************************************
	> File Name: 1-6_print_pid.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月08日 星期日 20时25分57秒
 ************************************************************************/

#include "apue.h"
int main(void)
{
    printf("hello world from process ID %ld\n", (long)getpid());
    exit(0);
}


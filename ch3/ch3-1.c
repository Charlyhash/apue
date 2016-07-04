/*************************************************************************
	> File Name: ch3-1.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月31日 星期二 14时55分20秒
 ************************************************************************/

#include<stdio.h>
#include "apue.h"

int main()
{
    if (lseek(STDIN_FILENO,0,SEEK_CUR) == 1)
        printf("cannot seek\n");
    else
        printf("seek OK\n");

    exit(0);
}

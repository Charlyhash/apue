/*************************************************************************
	> File Name: ch3-2.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月31日 星期二 15时05分50秒
 ************************************************************************/

#include<stdio.h>
#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghijk";
char buf2[] = "ABCDEFGHIJK";

int main()
{
    int fd;
    if ((fd=creat("file.hole", FILE_MODE)) < 0)
        err_sys("creat error");
    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    //offset now  = 10
    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");
    //offset now = 16384
    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");
    //offset now=16394
    
    exit(0);

}

#ifndef __SHM_DATA_H__
#define __SHM_DATA_H__

#include <stdio.h>
#include <stdlib.h>

#define TEXT_SZ 2048

struct shared_use_st
{
    int written;//flag:0 writeable, others readable
    char text[TEXT_SZ];//record text
};

void err_exit(const char* m)
{
    perror(m);
    exit(EXIT_FAILURE);
}

#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include "shmdata.h"

int main()
{
    int running = 1;
    void* shm = NULL;
    struct shared_use_st* shared = NULL;
    char buffer[BUFSIZ];//the text
    int shmid;
    //create
    shmid = shmget((key_t)1212, sizeof(struct shared_use_st), 0666|IPC_CREAT);
    if (shmid == -1)
        err_exit("shmget error!");
    shm = shmat(shmid, (void*)0,0);
    if (shm == (void*)-1)
        err_exit("shmat error!");
    printf("memory attached at %x\n", (int)shm);

    shared = (struct shared_use_st*)shm;
    while(running)
    {
        while (shared->written == 1)
        {
            sleep(1);
            printf("Waiting ...\n");
        }

        printf("Enter some text:\n");
        fgets(buffer, BUFSIZ, stdin);
        strncpy(shared->text, buffer,TEXT_SZ);
        shared->written = 1;
        if (strncmp(buffer, "end", 3) == 0)
            running = 0;
    }

    if (shmdt(shm) == -1)
        err_exit("shmdt failed!");
    sleep(2);
    exit(0);
}

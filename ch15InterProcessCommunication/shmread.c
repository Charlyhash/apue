#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "shmdata.h"

int main()
{
    int running = 1;
    void* shm = NULL; //address of the shared memory
    struct shared_use_st *shared;
    int shmid;
    //create shared memory
    shmid = shmget((key_t)1212, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1)
        err_exit("create shared memory error!");

    //attach address to the process
    shm = shmat(shmid, 0, 0);
    if (shm == (void*)-1)
        err_exit("shmat error.");
    printf("\n Memory attached at %X\n", (int)shm);

    //set shared memory
    shared = (struct shared_use_st*)shm;
    shared->written = 0;//fist write
    while (running)
    {
        //read process
        if (shared->written != 0)
        {
            //print the text
            printf("You wrote : %s\n", shared->text);
            sleep(rand() % 3);
            //then set shared writable
            shared->written = 0;
            if (strncmp(shared->text, "end", 3) == 0)
                running = 0;
        }
        else// other process is writing text
            sleep(1);
    }

    if (shmdt(shm) == -1)
        err_exit("shmdt error.");
    if (shmctl(shmid, IPC_RMID, 0) == -1)
        err_exit("shctl failed!");

    exit(0);
}

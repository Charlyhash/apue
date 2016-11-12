#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>

union semun
{
    int val;
    struct semid_ds* buf;
    unsigned short* array;
};

static int sem_id = 0;

void err_exit(const char* m)
{
    perror(m);
    exit(EXIT_FAILURE);
}


int set_semvalue()
{
    //init semaphores
    union semun sem_union;
    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
        //err_exit("init sempaores error!");
        return 0;

    return 1;
}

void del_semvalue()
{
    union semun sem_union;

    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
        err_exit("delete semaphores error!");
}

int sempahore_p()
{
    //p operator
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1)
       // err_exit("p operator error!");
       return 0;

    return 1;
}

int semaphore_v()
{
    //v operator
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1)
        //err_exit("v operator error!");
        return 0;

    return 1;
}

int main(int argc, char** argv)
{
    char message = 'x';
    int i = 0;

    //create semaphore
    sem_id = semget((key_t)1212, 1, 0666 | IPC_CREAT );

    if (argc > 1)
    {
        //first use semaphore
        if (!set_semvalue())
            err_exit("init semaphore error!");
        message = argv[1][0];
        sleep(2);
    }

    for (i = 0; i < 10; ++i)
    {
        //进入临界区
        if(!sempahore_p())
            err_exit("p operator error!");
        printf("%c ", message);
        fflush(stdout);
        sleep(rand() % 3);
        printf("%c ", message);
        fflush(stdout);
        if (!semaphore_v())
            err_exit("p operator error!");
        sleep(rand() % 2);
    }

    sleep(10);
    printf("\n %d - finished", getpid());

    if (argc > 1)
    {
        sleep(3);
        del_semvalue();
    }

    exit(0);
}

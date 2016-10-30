#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void cleanup(void *arg)
{
    printf("clearnup: %s", (char*) arg);
}

void* thr_fn1(void* arg)
{
    printf("thread 1 start.\n");
    pthread_cleanup_push(cleanup, "thread 1 first handle");
    pthread_cleanup_push(cleanup, "thread 1 second handle");
    printf("thread1 push complete\n");
    if (arg)
        return (void*)1;

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);

    return (void*)1;
}

void* thr_fn2(void* arg)
{
    printf("thread 2 start.\n");
    pthread_cleanup_push(cleanup, "thread 2 first handle");
    pthread_cleanup_push(cleanup, "thread 2 second handle");
    if (arg)
        return (void*)1;

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);

    return (void*)1;
}

int main()
{
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, (void*)1);
    if (err != 0)
    {
        printf("create thread1 error!\n");
        exit(1);
    }
    err = pthread_create(&tid2, NULL, thr_fn2, (void*)1);
    if (err != 0)
    {
        perror("create thread2 error!\n");
        exit(1);
    }
    err = pthread_join(tid1, &tret);
    if (err != 0)
    {
        perror("join thread 1 error!\n");
        exit(1);
    }
    printf("thread 1 exit code : %ld\n",(long)tret );
    err = pthread_join(tid2, &tret);
    if (err != 0)
    {
        perror("join thread 2 error!\n");
        exit(1);
    }
    printf("thread 2 exit code : %ld\n", (long)tret);

    exit(0);
}

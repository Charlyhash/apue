// 使用条件变量的一个例子：
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREAD 3//线程数目
#define TCOUNT 5    //单线程轮询次数
#define COUNT_LIMIT 7//发送信号的次数
int count = 0; //全局累加量

pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

//增加count
void *inc_count(void *t)
{
    int i;
    long my_id = (long)t;

    for (i = 0; i < TCOUNT; ++i)
    {
        pthread_mutex_lock(&count_mutex);
        count++;
        //检查count的值，满足条件就发送信号
       if (count < COUNT_LIMIT)
       {
            printf("inc_count(): thread %ld, count = %d Threshold reached. ",
                    my_id, count);
            //发送信号
            pthread_cond_signal(&count_threshold_cv);
            printf("Just sent signal.\n");
        }

       printf("inc_count() : thread %ld, count = %d, unlocking muext.\n",
               my_id, count);
       pthread_mutex_unlock(&count_mutex);

       sleep(1);
    }

    pthread_exit(NULL);
}

//等待线程
void *watch_count(void* t)
{
    long my_id = (long)t;
    printf("Starting watch_count(): thread %ld.\n", my_id);
    //锁定互斥量并等待信号，以原子的方式解锁互斥量。
    while ( count < COUNT_LIMIT)
    {
        pthread_mutex_lock(&count_mutex);
        printf("watch_count(): thread %ld go inot wait...\n", my_id);
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        printf("watch_count():thread %ld Condition signal received.\n", my_id);

        printf("watch_count():thread %ld count now = %d.\n", my_id, count);
        pthread_mutex_unlock(&count_mutex);
   }
    pthread_exit(NULL);
}

int main()
{
    int i;
    long t1 =1, t2 = 2, t3 = 3;

    pthread_t threads[3];
    pthread_attr_t attr;

    //初始化互斥量和条件变量对象
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threads[0], &attr, watch_count, (void*) t1);
    pthread_create(&threads[1], &attr, inc_count, (void*) t2);
    pthread_create(&threads[2], &attr, inc_count, (void*) t3);

    for (int i= 1; i < NUM_THREAD; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    //发送信号个i额监听线程
    //
    pthread_cond_signal(&count_threshold_cv);
    pthread_join(threads[0], NULL);
    printf("Main():Waited on %d theaads, final value of ocunt = %d.Done\n",
            NUM_THREAD, count);

    //清理线程
    //
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    pthread_exit(NULL);
}

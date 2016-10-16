#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include<setjmp.h>
#include <errno.h>
#include<time.h>

void pr_mask(const char* str)
{
    sigset_t sigset;
    int errno_save;

    errno_save = errno;     //保存的errno
    if (sigprocmask(0, NULL, &sigset) < 0)
    {
        printf("sigprocmask error!\n");
        exit(1);
    }
    else
    {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT))
            printf("SIGINT");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
         if (sigismember(&sigset, SIGUSR2))
            printf(" SIGUSR2");

        printf("\n");

    }
}

static void sig_usr1(int);
static void                  sig_alrm(int);
static sigjmp_buf            jmpbuf;
static volatile sig_atomic_t canjump;
int main(void)
{
    if(signal(SIGUSR1,sig_usr1)==SIG_ERR)
        printf("singnal SIGUSR1 error");
    if(signal(SIGALRM,sig_alrm)==SIG_ERR)
        printf("signal SIGALRM error");
    pr_mask("staring main : \n");
    if(sigsetjmp(jmpbuf,1))
    {
        pr_mask("ending main: \n");
        exit(0);
    }
    canjump=1;
    for(;;)
    {
        pause(); //终止保持信号接收
    }
}

static void sig_usr1(int siigno)
{
    time_t startime;
    if(canjump==0)
    {
        return ;
    }
    pr_mask("staring sig_usr1 function\n");
    alarm (3);
    startime=time(NULL);
    for(;;)
    {
        if(time(NULL)>startime +5)
            break;
    }
    pr_mask("finishing the function sig_usr1\n");
    canjump =0;
    siglongjmp(jmpbuf,1);//返回主函数同前一例中的longjmp作用类似

}
static void sig_alrm(int signo )
{
    pr_mask("int the function sig_alrm\n");
}

//使用sigaction实现signal函数
//除非特殊地要求老的不可靠语义，否则应当使用本实现的signal函数或者使用sigaction函数
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

Sigfunc* signal(int signo, Sigfunc func)
{
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (signo ==SIGALRM)
    {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    }
    else
        act.sa_flags |= SA_RESTART;

    if (sigaction(signo, &act, &oact) < 0)
       return SIG_ERR;
    return oact.sa_handler;
}

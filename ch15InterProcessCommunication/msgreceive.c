#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

#define BUFSIZE 512

struct msg_st
{
    long int msg_type;
    char text[BUFSIZE];
};

void err_exit(const char* m)
{
    perror(m);
    exit(EXIT_FAILURE);
}

int main()
{
    int running = 1;
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0;

    //create message queue
    msgid = msgget((key_t)1212, 0666 | IPC_CREAT);
    if (msgid == -1)
        err_exit("create message queue error");
    while (running)
    {
        //receive  message
        if (msgrcv(msgid, (void*)(&data), BUFSIZE, msgtype, 0) == -1)
            err_exit("recieve message error.");
        printf("You wrote:%s\n", data.text);

        if (strncmp(data.text, "end", 3) == 0)
            running = 0;
    }
    //delete message
    if (msgctl(msgid, IPC_RMID, 0) == -1)
        err_exit("delete message error.");

    exit(0);
};

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <sys/msg.h>

#define MAX_TEXT 512

struct msg_st
{
    long int msg_type;
    char text[MAX_TEXT];
};

void err_exit(const char* m)
{
    perror(m);
    exit(EXIT_FAILURE);
}

int main()
{
    int running = 1;
    struct msg_st data;
    char buffer[MAX_TEXT];
    int msgid = -1;

    //create message queue
    msgid = msgget((key_t)1212, 0666|IPC_CREAT);
    if (msgid == -1)
        err_exit("create message queue error.");
    while (running)
    {
        printf("Enter some text:\n");
        fgets(buffer, MAX_TEXT, stdin);
        data.msg_type = 1;
        strcpy(data.text, buffer);
        if (msgsnd(msgid, (void *)(&data), MAX_TEXT, 0) == -1)
            err_exit("send message error.");
        if (strncmp(buffer, "end", 3) == 0)
            running = 0;
        sleep(1);
    }

    exit(0);
}

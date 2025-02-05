#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>

#define MAX 10
#define BUF_SIZE 1000
struct mesg_buffer {
    long mesg_type;
    char mesg_text[BUF_SIZE];
}message;

int main() {
    key_t key;
    int msgid;
    key = ftok("progfile",65);
    msgid = msgget(key,0666|IPC_CREAT);
    msgrcv(msgid,&message,sizeof(message),1,0);
    printf("Msg recieved:%s\n",message.mesg_text);
    msgctl(msgid,IPC_RMID,NULL);    //destroy
    return 0;
}

/*
rtk5@penguin:~/sem4/OS/week 5$ gcc 4\)msg_recev.c 
rtk5@penguin:~/sem4/OS/week 5$ ./a.out
Msg recieved:Hi guys gm
*/
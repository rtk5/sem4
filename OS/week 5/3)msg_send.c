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
    printf("Enter the msg to be passed\n");
    read(0,message.mesg_text,BUF_SIZE);     //reading particular message
    printf("Msg being sent:%s\n",message.mesg_text);
    key = ftok("progfile",65);  //ftok -> to create key ,progfile-> key generator      ,code -> to create a dynamic key
    msgid = msgget(key,0666|IPC_CREAT); //to create msg queue & giving read write access
    message.mesg_type=1;    //setting flag
    msgsnd(msgid,&message,sizeof(message),0);
    sleep(60);
    return 0;
}

/*
rtk5@penguin:~/sem4/OS/week 5$ gcc 3\)msg.c 
rtk5@penguin:~/sem4/OS/week 5$ ./a.out
Enter the msg to be passed
Hi guys gm                 
Msg being sent:Hi guys gm
*/
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main() {
    void *shared_memory;
    char buff[100];
    int shmid;
    shmid=shmget((key_t)1122,1024,0666);
    printf("Key of shared memory is %d\n",shmid);
    shared_memory = shmat(shmid,NULL,0);
    printf("Process attached at %p\n",shared_memory);
    printf("Data read from shared memory is :%s\n",(char*)shared_memory);
}


/*
rtk5@penguin:~/sem4/OS/week 5$ gcc reciever.c 
rtk5@penguin:~/sem4/OS/week 5$ ./a.out
Key of shared memory is 12
Process attached at 0x7fd4e564d000
Data read from shared memory is :hello my name is rtk
*/
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main() {
    void *shared_memory;
    char buff[100];
    int shmid;

    shmid = shmget((key_t)1122,1024,0666|IPC_CREAT);
    printf("Key of shared memory is %d\n",shmid);   //unique identifier
    
    shared_memory = shmat(shmid,NULL,0);    //attach
    printf("Process attached at %p\n",shared_memory);   //address
    printf("Enter some data to write to shared memory\n");  //write inside shared memory
    
    read(0,buff,100);   
    strcpy(shared_memory,buff); //copying data to shared mem
    printf("Data read from shared memory is %s\n",(char*)shared_memory);
}



/*
rtk5@penguin:~/sem4/OS/week 5$ gcc d.c 
rtk5@penguin:~/sem4/OS/week 5$ ./a.out
Key of shared memory is 12
Process attached at 0x7f47b9b78000
Enter some data to write to shared memory
hello my name is rtk
Data read from shared memory is hello my name is rtk
*/
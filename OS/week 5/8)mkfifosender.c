#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>       // for controlling read or write mode
int main() {
    int res,n;
    res = open("fifo1",O_WRONLY);   // write only mode
    write(res,"message",7);
    printf("Sender process %d sent the data\n",getpid());
}


//no output because sender and reciever must be present

/*
rtk5@penguin:~/sem4/OS/week 5$ gcc 8\)mkfifosender.c 
rtk5@penguin:~/sem4/OS/week 5$ ./a.out
^C
*/
#include<sys/types.h>
#include<stdio.h>
#include<sys/stat.h>

int main() {
    int res,n;
    res = mkfifo("fifo1",0777);     //create blocked commn link
    printf("named pipe created\n");
}

/*
rtk5@penguin:~/sem4/OS/week 5$ gcc 7\)mkfifo.c 
rtk5@penguin:~/sem4/OS/week 5$ ./a.out
named pipe created
*/
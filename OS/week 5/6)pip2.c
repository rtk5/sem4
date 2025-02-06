#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>        //to create fn called pipe
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

int main() {
    FILE *rd;
    char buffer[50];
    sprintf(buffer,"name first");
    rd = popen("wc -c","w");
    fwrite(buffer,sizeof(char),strlen(buffer),rd); // to write data into the pipe
    pclose(rd);
}

/*
rtk5@penguin:~/sem4/OS/week 5$ gcc 6\)pip2.c 
rtk5@penguin:~/sem4/OS/week 5$ ./a.out
10
*/
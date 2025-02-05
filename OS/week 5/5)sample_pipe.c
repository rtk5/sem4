#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>        //to create fn called pipe
#include<sys/wait.h>

int main() {
    int fd[2],n;
    char buff[100];
    pid_t p;
    pipe(fd);
    p = fork();
    if(p>0) {
        printf("Parent passing value to child\n");
        write(fd[1],"hello\n",6); //write mode
    }
    else {
        printf("Child printing recieved value\n");
        n = read(fd[0],buff,100);
        write(1,buff,n);
    }
}

/*
rtk5@penguin:~/sem4/OS/week 5$ gcc 5\)sample_pipe.c 
rtk5@penguin:~/sem4/OS/week 5$ ./a.out
Parent passing value to child
Child printing recieved value
hello
*/
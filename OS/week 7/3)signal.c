#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main() {
    pid_t p1;
    p1 = fork();
    if(p1>0) {
        sleep(1);
        printf("This is parent process id = %d\n",getpid());
        kill(p1,SIGSTOP);
        printf("This is parent after pausing the child. Process id = %d\n",getpid());
        sleep(1);
        kill(p1,SIGCONT);
        printf("This is parent after restarting the child. Process id=%d\n",getpid());
        sleep(1);
        kill(p1,SIGKILL);
        sleep(1);
        printf("This is parent after terminating the child. Process id=%d\n",getpid());
    }
    else if (p1==0) {
        while(1)
        printf("This is child process. Process id=%d,parent process id=%d\n",getpid(),getppid());
    }
    else {
        printf("Fork creation failed\n");
    }
}

// child process keeps looping then 
/*This is child process. Process id=3955,parent process id=3954
This is child process. Process id=3955,parent process id=3954
This is child process. Process id=3955,parent process id=3954
This is child process. Process id=3955,parent process id=3954
This is child process. Process id=3955,parent process id=3954
This is child process. Process id=3955,parent process id=3954
This is child process. Process id=3955,parent process id=3954
This is child process. Process id=3955,parent process id=3954
This is child process. Process id=3955,parent process id=3954
This is child process. Process id=3955,parent process id=3954This is parent after terminating the child. Process id=3954*/

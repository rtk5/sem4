// program to demonstrate creation of child processes and executing commands using fork(), execl() and wait() 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1, p2;

    int y = 0;

    p1 = fork();

    if (p1 > 0) //parent process
    {
        wait(NULL);     // waits until child executes

        y = y - 1;

        printf("This is parent. Process Id = %d, y = %d\n", getpid(), y);

        execl("/bin/ls", "/home/suresh/OS", NULL);
    }
    else if (p1 == 0) // child process 
    {
        p2 = fork();    // creation of grandchild

        if (p2 > 0)
        {
           wait(NULL);      //waits until grandchild executes
        }
        else if (p2 == 0)
        {
           y = y + 5;
           
           printf("This is grandchild. Process Id = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);

           execl("/bin/ls", "/home/rithvikmatta/sem4/OS/week 2", "-r", NULL);

           exit(0);
        }

        y = y + 1;

        printf("This is child. Process Id = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);

        char *a[] = {NULL};

        execv("/home/rithvikmatta/sem4/OS/week 2/c.out", a);    

        exit(0);
    }
    else //fork failed
    {
        printf("fork creation failed!!!\n");
    }
}

/*OUTPUT ->>
rithvikmatta@penguin:~/sem4/OS/week 2$ ./a.out
This is grandchild. Process Id = 13470, Parent Process Id = 13469, y = 5
zombie.c  wait.c  sample.c  orphan.c  fork.c  execv.c  c.out  a.out
This is child. Process Id = 13469, Parent Process Id = 13468, y = 1
The sum of 2 and 3 is 5
This is parent. Process Id = 13468, y = -1
a.out  c.out  execv.c  fork.c  orphan.c  sample.c  wait.c  zombie.c
*/
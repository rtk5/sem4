// program to demonstrate fork() 

#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t p1;   //pid_t to create a process

    int i = 0, y = 0;
   
    p1 = fork();    // child process

    if (p1 > 0) //parent process
    {
       for (i = 0; i < 5; i++)
       {
          sleep(i); // hold porgram

          y = y - 1;

          printf("This is parent. Process Id = %d, y = %d\n", getpid(), y);         //process id
       }
    }
    else if (p1 == 0) // child process 
    {
       for (i = 0; i < 5; i++)
       {
          sleep(i);

          y = y + 1;

          printf("This is child. Process Id = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);   //child process id ppid ->parent process id
       }
    }
    else //fork failed
    {
        printf("fork creation failed!!!\n");
    }
}


/*OUTPUT-->>
rithvikmatta@penguin:~/sem4/OS/week 2$ ./a.out
This is parent. Process Id = 7904, y = -1
This is child. Process Id = 7905, Parent Process Id = 7904, y = 1
This is parent. Process Id = 7904, y = -2
This is child. Process Id = 7905, Parent Process Id = 7904, y = 2
This is parent. Process Id = 7904, y = -3
This is child. Process Id = 7905, Parent Process Id = 7904, y = 3
This is parent. Process Id = 7904, y = -4
This is child. Process Id = 7905, Parent Process Id = 7904, y = 4
This is parent. Process Id = 7904, y = -5
This is child. Process Id = 7905, Parent Process Id = 194, y = 5
*/
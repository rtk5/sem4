#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
   int rv = 0;

   printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());

   rv = setuid(1000);

   if (rv < 0)
	   printf("error setting uid\n");

   rv = setgid(1000);

   if (rv < 0)
	   printf("error setting gid\n");

   printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());

   exit(0);
}

/*
rithvikmatta@penguin:~/sem4/OS/week 15$ gcc demo_getuid.c 
rithvikmatta@penguin:~/sem4/OS/week 15$ ./a.out
real uid = 1000, effective uid = 1000
real uid = 1000, effective uid = 1000
*/
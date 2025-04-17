#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc, char *argv[])
{
   umask(0);
   umask(S_IROTH | S_IWOTH);
   
   if (creat(argv[1], RWRWRW) < 0)
      printf("Error creating the file\n");

   exit(0);
}

/*output-->

rithvikmatta@penguin:~/sem4/OS/week 15$ gcc demo_umask.c 
rithvikmatta@penguin:~/sem4/OS/week 15$ touch sample.txt
rithvikmatta@penguin:~/sem4/OS/week 15$ ./a.out sample.txt
rithvikmatta@penguin:~/sem4/OS/week 15$ ls -l sample.txt
-rw-r--r-- 1 rithvikmatta rithvikmatta 0 Apr 17 10:40 sample.txt

*/
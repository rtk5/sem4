#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
   int fd = creat(argv[1], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

   if (fd == -1)
      printf("unable to create file\n");

   for (int i = 0; i < 10; i++)
      write(fd, "0123456789", 10);

   close(fd);

   if (truncate(argv[1], 50) < 0)
      printf("unable to truncate the file\n");

   exit(0);
}

/*
rithvikmatta@penguin:~/sem4/OS/week 15$ gcc demo_truncate.c 
rithvikmatta@penguin:~/sem4/OS/week 15$ ./a.out sample.txt
rithvikmatta@penguin:~/sem4/OS/week 15$ ls -l sample.txt
-rw-r--r-- 1 rithvikmatta rithvikmatta 50 Apr 17 10:47 sample.txt
rithvikmatta@penguin:~/sem4/OS/week 15$ hexdump -c sample.txt
0000000   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5
0000010   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1
0000020   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7
0000030   8   9                                                        
0000032
rithvikmatta@penguin:~/sem4/OS/week 15$ 


sample.txt -->
01234567890123456789012345678901234567890123456789
*/
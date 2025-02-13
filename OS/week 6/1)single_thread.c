#include<stdio.h>
#include<pthread.h>
void *computation(){
    printf("First thread program \n");
    return 0;
    }

int main(){
pthread_t thread1;
pthread_create(&thread1,NULL,computation,NULL);
pthread_join(thread1,NULL);
return 0;
}

/*
rithvikmatta@penguin:~/sem4/OS/week 6$ gcc 1\)single_thread.c 
rithvikmatta@penguin:~/sem4/OS/week 6$ ./a.out
First thread program 
*/
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
void *my_function(void *arg) {
    sem_wait(&mutex);
    printf("Entered critical section \n");
    sleep(4);
    printf("Exiting\n");
    sem_post(&mutex);
}

int main() {
    pthread_t t1,t2;
    sem_init(&mutex,0,1);
    pthread_create(&t1,NULL,my_function,NULL);
    sleep(2);
    pthread_create(&t2,NULL,my_function,NULL);pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
}
/*
rithvikmatta@penguin:~/sem4/OS/week 6$ gcc 5\)semaphore.c 
rithvikmatta@penguin:~/sem4/OS/week 6$ ./a.out
Entered critical section 
Exiting
Entered critical section 
Exiting
*/
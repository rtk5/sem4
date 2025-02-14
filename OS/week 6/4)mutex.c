#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[2];
int counter;
pthread_mutex_t lock;
void *thread_function(void *arg) {
    pthread_mutex_lock(&lock);
    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d has started\n", counter);
    for (i = 0; i < (0xFFFFFFFF); i++);
    printf("\n Job %d has finished\n",counter);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    int i = 0;
    int threadcrea;
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
    while (i < 2) {
        threadcrea = pthread_create(&(tid[i]), NULL, &thread_function, NULL);
        i++;
    }
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
}
/*
rithvikmatta@penguin:~/sem4/OS/week 6$ gcc 4\)mutex.c 
rithvikmatta@penguin:~/sem4/OS/week 6$ ./a.out

 Job 1 has started

 Job 1 has finished

 Job 2 has started

 Job 2 has finished
 */
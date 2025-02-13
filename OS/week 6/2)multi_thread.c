#include <stdio.h>
#include <pthread.h>

void *computation(void *add) {
    long *add_num = (long *) add;  // Correct typecasting
    printf("Add: %ld\n", *add_num);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    long value = 5, value1 = 1;

    // Create thread1
    pthread_create(&thread1, NULL, computation, &value);
    pthread_join(thread1, NULL);

    // Create thread2
    pthread_create(&thread2, NULL, computation, &value1);
    pthread_join(thread2, NULL);

    return 0;
}
/*
rithvikmatta@penguin:~/sem4/OS/week 6$ gcc 2\)multi_thread.c 
rithvikmatta@penguin:~/sem4/OS/week 6$ ./a.out
Add: 5
Add: 1*/
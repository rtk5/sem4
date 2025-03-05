#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct Student {
    char name[50];
    char SRN[20];
    int sem;
    float CGPA;
};

int main() {
    void *shared_memory;
    int shmid;

    shmid = shmget((key_t)1122, sizeof(struct Student), 0666);
    printf("Key of shared memory is %d\n", shmid);

    shared_memory = shmat(shmid, NULL, 0);
    printf("Process attached at %p\n", shared_memory);

    struct Student *student = (struct Student *)shared_memory;

    printf("\nStudent Information:\n");
    printf("Name: %s\n", student->name);
    printf("SRN: %s\n", student->SRN);
    printf("Semester: %d\n", student->sem);
    printf("CGPA: %.2f\n", student->CGPA);

    return 0;
}

#include <stdio.h>      
#include <fcntl.h>      
#include <unistd.h>     
#include <string.h>     

int main() {
    int fd;
    char buffer[] = "Hello from system call!";
    char filePath[] = "demo.txt";

    fd = open(filePath, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    if (write(fd, buffer, 20) < 0) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    off_t endPos = lseek(fd, 0, SEEK_END);
    if (endPos == -1) {
        perror("Error with SEEK_END");
        close(fd);
        return 1;
    }
    printf("File pointer moved to end: %ld\n", (long)endPos);

    off_t startPos = lseek(fd, 0, SEEK_SET);
    if (startPos == -1) {
        perror("Error with SEEK_SET");
        close(fd);
        return 1;
    }
    printf("File pointer moved to start: %ld\n", (long)startPos);

    close(fd);
    return 0;
}

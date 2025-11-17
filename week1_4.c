#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid1 = fork();

    if (pid1 == 0) {
        sleep(3);
        printf("Orphan Process Example:\n");
        printf("Child PID: %d, New Parent PID: %d\n", getpid(), getppid());
    } else {
        printf("Parent exiting early to create orphan...\n");
        exit(0);
    }

    sleep(5);

    pid_t pid2 = fork();

    if (pid2 == 0) {
        printf("Zombie Process Example:\n");
        printf("Child PID: %d created and exiting...\n", getpid());
        exit(0);
    } else {
        sleep(10);
        printf("Parent didn't wait for child — zombie created.\n");
    }
    return 0;
}
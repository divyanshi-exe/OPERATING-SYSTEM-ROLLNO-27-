
#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        printf("Child (PID: %d) running...\n", getpid());
        sleep(2);
        printf("Child completed.\n");
        exit(0);
    } else {
        wait(NULL);
        printf("Parent (PID: %d) waited for child.\n", getpid());
    }
    return 0;
}
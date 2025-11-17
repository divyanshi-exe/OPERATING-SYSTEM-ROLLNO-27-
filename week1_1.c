#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;
    printf("Before fork call\n");
    pid = fork();

    if (pid < 0)
        printf("Fork failed!\n");
    else if (pid == 0)
        printf("This is the child process.\n");
    else
        printf("This is the parent process.\n");

    printf("Process with PID %d finished execution.\n", getpid());
    return 0;
}
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0)
        printf("Fork failed!\n");
    else if (pid == 0) {
        printf("Child Process:\n");
        printf("My PID: %d\n", getpid());
        printf("My Parent PID: %d\n", getppid());
    } else {
        printf("Parent Process:\n");
        printf("My PID: %d\n", getpid());
        printf("My Child PID: %d\n", pid);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Before execlp() call\n");

    execlp("cmd.exe", "cmd.exe", "/c", "dir", NULL);

    perror("execlp failed");
    return 1;
}
dir
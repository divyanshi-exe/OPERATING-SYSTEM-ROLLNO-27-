#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define SIZE 4096
#define MAXLINES 256
static void rstrip(char *s){
    size_t n = strlen(s);
    while (n && (s[n-1] == '\n' || s[n-1] == '\r')) s[--n] = '\0';
}
int main() {
    int fd1, fd2;
    char buf1[SIZE], buf2[SIZE];
    fd1 = open("me.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd1 < 0) { perror("me.txt open"); return 1; }
    const char *me =
        "Name: Abc\n"
        "College: XYZ\n"
        "Hobby: Coding\n";
    if (write(fd1, me, strlen(me)) < 0) { perror("me.txt write"); return 1; }
    close(fd1);

    fd2 = open("friend.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd2 < 0) { perror("friend.txt open"); return 1; }
    const char *fr =
        "Name: Xyz\n"
        "College: XYZ\n"
        "Hobby: Reading\n";
    if (write(fd2, fr, strlen(fr)) < 0) { perror("friend.txt write"); return 1; }
    close(fd2);
    fd1 = open("me.txt", O_RDONLY);
    if (fd1 < 0) { perror("me.txt reopen"); return 1; }
    fd2 = open("friend.txt", O_RDONLY);
    if (fd2 < 0) { perror("friend.txt reopen"); return 1; }
    ssize_t n1 = read(fd1, buf1, SIZE - 1);
    if (n1 < 0) { perror("me.txt read"); return 1; }
    buf1[n1] = '\0';
    close(fd1);
    ssize_t n2 = read(fd2, buf2, SIZE - 1);
    if (n2 < 0) { perror("friend.txt read"); return 1; }
    buf2[n2] = '\0';
    close(fd2);
    char *lines1[MAXLINES]; int c1 = 0;
    char *lines2[MAXLINES]; int c2 = 0;
    char *save1 = NULL, *save2 = NULL;
    char *tok = strtok_r(buf1, "\n", &save1);
    while (tok && c1 < MAXLINES) { rstrip(tok); lines1[c1++] = tok; tok = strtok_r(NULL, "\n", &save1); }

    tok = strtok_r(buf2, "\n", &save2);
    while (tok && c2 < MAXLINES) { rstrip(tok); lines2[c2++] = tok; tok = strtok_r(NULL, "\n", &save2); }
    printf("\nMatching lines in both files:\n");
    int found = 0;
    for (int i = 0; i < c1; i++) {
        for (int j = 0; j < c2; j++) {
            if (strcmp(lines1[i], lines2[j]) == 0) {
                printf("%s\n", lines1[i]);
                found = 1;
            }
        }
    }
    if (!found) printf("(none)\n");
    return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {

    int pide_fd[3][2];

    pipe(pide_fd[0]);
    if (pipe(pide_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    if (fork() == 0) {
        close(pide_fd[0][0]);

        dup2(pide_fd[0][1], STDOUT_FILENO);
        close(pide_fd[0][1]);

        execlp("grep", "grep", "root", NULL);
        _exit(1);
    }
    close(pide_fd[0][1]);

    pipe(pide_fd[1]);
    if (fork() == 0) {
        close(pide_fd[1][0]);

        dup2(pide_fd[0][0], STDIN_FILENO);
        close(pide_fd[0][0]);

        dup2(pide_fd[1][1], STDOUT_FILENO);
        close(pide_fd[1][1]);

        execlp("cut", "cut", "-d:", "-f1", NULL);
        _exit(1);
    }
    close(pide_fd[0][0]);
    close(pide_fd[1][1]);

    pipe(pide_fd[2]);
    if (fork() == 0) {
        close(pide_fd[2][0]);

        dup2(pide_fd[1][0], STDIN_FILENO);
        close(pide_fd[1][0]);

        dup2(pide_fd[2][1], STDOUT_FILENO);
        close(pide_fd[2][1]);

        execlp("wc", "wc", "-l", NULL);
        _exit(1);

    }
    close(pide_fd[1][0]);
    close(pide_fd[2][1]);

    if (fork() == 0) {

        dup2(pide_fd[2][0], STDOUT_FILENO);
        close(pide_fd[2][0]);
        execlp("sort", "sort", NULL);
        _exit(1);
    }
    close(pide_fd[2][0]);

    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}

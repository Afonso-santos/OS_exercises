#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]) {

    int pide_fd[2];
    if (pipe(pide_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    if (fork() == 0) {
        close(pide_fd[0]);
        dup2(pide_fd[1], STDOUT_FILENO); // dup2(pide_fd[1], 1);
        close(pide_fd[1]);
        execlp("ls", "ls", NULL);
        _exit(1);
    }
    close(pide_fd[1]);

    if (fork() == 0) {

       // close(pide_fd[1]);
        dup2(pide_fd[0], STDIN_FILENO); // dup2(pide_fd[0], 0);
        close(pide_fd[0]);

        execlp("wc", "wc", NULL);
        _exit(1);
    }
    close(pide_fd[0]);
   // close(pide_fd[1]);
    
    wait(NULL);
    wait(NULL);
    return 0;
}

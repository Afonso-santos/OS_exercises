#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
 
    int pide_fd[2];
    if(pipe(pide_fd) == -1){
        perror("pipe");
        exit(1);
    }

    if(fork()==0){

        close(pide_fd[1]);
        dup2(pide_fd[0], STDIN_FILENO); // dup2(pide_fd[0], 0);
        close(pide_fd[0]);

        execlp("wc", "wc", NULL);
        _exit(1);
    }
    else{
        close(pide_fd[0]);
        int bytes_read = 0;
        char buffer[10];
        while ((bytes_read = read(STDIN_FILENO, buffer, 10)) > 0) {
            write(pide_fd[1], buffer, bytes_read);
        }

        close(pide_fd[1]);
        wait(NULL);
        return 0;
    }
}
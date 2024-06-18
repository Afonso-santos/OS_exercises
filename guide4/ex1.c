#include <unistd.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int main(){
    int pipe_fd[2];
    pipe(pipe_fd);
    if(fork() == 0){
        close(pipe_fd[0]);
        int i = 10;
        write(pipe_fd[1], &i, sizeof(int));
        //sleep(100);
        _exit(0);
    }
    close(pipe_fd[1]);
    
    int i = -1;
    read(pipe_fd[0], &i, sizeof(int));
    wait(NULL);
    printf("i = %d\n", i);
    
    return 0;
}
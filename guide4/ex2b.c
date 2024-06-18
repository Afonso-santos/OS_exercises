#include <unistd.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>


int main(){
    int pipe_fd[2];
    pid_t pid;
    int i ;

    if(pipe(pipe_fd) == -1){
        perror("pipe");
        return 1;
    }

    
    if((pid = fork()) == 0){
        close(pipe_fd[0]);
        for( i = 0; i < 1000000; i++){

            printf("i = %d\n", i);
            
            write(pipe_fd[1], &i, sizeof(int));
        }
         printf("teste  \n");
         close(pipe_fd[1]);
        _exit(0);
    }

    close(pipe_fd[1]);

   
    sleep(5);
    while(read(pipe_fd[0], &i, sizeof(int)) > 0){
 
    printf("data = %d\n", i);
    }
    wait(NULL);   
    return 0;

}
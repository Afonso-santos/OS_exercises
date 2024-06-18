#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int status;
    pid_t wait_pid;
    for (int i = 1; i <= 10;i++) {
        printf("--(%d)--\n", i);
        if (fork() == 0) {
            printf("child pid : %d\n", getpid());
            printf("child ppid: %d\n", getppid());
            _exit(i);
        
        }else{

            wait_pid = wait(&status);

            if (WIFEXITED(status)) {
                printf("exit status of pid[%d]: %d\n", wait_pid, WEXITSTATUS(status));
                printf("child process terminated normally\n");
            }else {
                printf("child process terminated abnormally\n");
            }
            printf("\n");
        }
    }
}
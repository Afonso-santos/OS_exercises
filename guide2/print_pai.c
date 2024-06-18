#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int status;
    pid_t wait_pid;
    //  1 exercise
        // printf("pid : %d\n", getpid());
        // printf("ppid: %d\n", getppid());
    // 
    if ((pid = fork()) == 0) {
        // sleep(5); orphan process
        printf("child pid : %d\n", getpid());
        printf("child ppid: %d\n", getppid());
        
        _exit(0);
    }

    // return 0; orphan process

    printf("parent pid : %d\n", getpid());
    printf("parent ppid: %d\n", getppid());

    // zombie process
    sleep(30);

    wait_pid = wait(&status);

    if (WIFEXITED(status)) {
        printf("exit status of pid[%d]: %d\n", wait_pid, WEXITSTATUS(status));
        printf("child process terminated normally\n");
    }else {
        printf("child process terminated abnormally\n");
    }



    getchar();
    return 0;
}
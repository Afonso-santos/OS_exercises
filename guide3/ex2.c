#include <unistd.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    pid_t pid;
    for (int i = 0;i < 3;i++) {
        if (fork() == 0) {
            printf("%d child pid : %d\n", i, getpid());
            int retunr_value = execlp("ls", "ls", "-l", NULL);
            printf("return value: %d\n", retunr_value);
            _exit(i);
        }
    }

    for (int i = 0;i < 3;i++) {
        int status=0;
        pid_t wait_pid = wait(&status);
        // int return_value = execlp("ls", "ls", "-l", NULL);
        if (WIFEXITED(status)) {
            printf("exit status of pid[%d]: %d\n", wait_pid, WEXITSTATUS(status));
            printf("child process terminated normally\n");

        }
    }
}


// if((pid = fork()) == 0) {
//     printf("pid : %d\n", getpid());
//     int return_value = execlp("ls", "ls", "-l", NULL);
//     printf("return value: %d\n", return_value);
//     _exit(-1);
// } else {
//     int status=0;
//      wait(&status);
//     if (WIFEXITED(status)) {
//         printf("exit status: %d\n",  WEXITSTATUS(status));
//         printf("child process terminated normally\n");
//     }else {
//         printf("child process terminated abnormally\n");
//     }
// }




/*
for(int i=0; i<3; i++){
        if((pid = fork()) == 0) {
            printf("pid : %d\n", getpid());
            int return_value = execlp("ls", "ls", "-l", NULL);
            printf("return value: %d\n", return_value);
        } else {
            int status;
            pid_t wait_pid = wait(&status);
            if (WIFEXITED(status)) {
                printf("exit status of pid[%d]: %d\n", wait_pid, WEXITSTATUS(status));
                printf("child process terminated normally\n");
            }else {
                printf("child process terminated abnormally\n");
            }
        }
    }



*/
#include <unistd.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    pid_t pid;
    printf("pid : %d\n", getpid());
    int return_value = execlp("ls", "ls", "-l", NULL);
    /**
     * com outro comando:
     * execl("/bin/ls", "ls", "-l", NULL);
     * 
     * Com vetor:
     * exec_args[]={"/bin/ls", "ls", "-l", NULL};
     * execvp("ls", exec_args);
    */

    printf("return value: %d\n", return_value);
    return 0;

}

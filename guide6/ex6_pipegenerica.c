

int main(int argc, char* argv[]) {
    int count = 4 - 1;
    int pide_fd[count][2];

    for(int i = 0; i < count; i++){

        if (pipe(pide_fd[i]) == -1) {
            perror("pipe");
            exit(1);
        }

        if (fork() == 0) {
            for(int j = 0; j < count; j++){
                if(j != i){
                    close(pide_fd[j][0]);
                    close(pide_fd[j][1]);
                }
            }

            if(i == 0){
                dup2(pide_fd[i][1], STDOUT_FILENO);
                close(pide_fd[i][1]);
                execlp("ls", "ls", NULL);
                _exit(1);
            }
            else if(i == 1){
                dup2(pide_fd[i-1][0], STDIN_FILENO);
                close(pide_fd[i-1][0]);
                dup2(pide_fd[i][1], STDOUT_FILENO);
                close(pide_fd[i][1]);
                execlp("wc", "wc", NULL);
                _exit(1);
            }
            else if(i == 2){
                dup2(pide_fd[i-1][0], STDIN_FILENO);
                close(pide_fd[i-1][0]);
                dup2(pide_fd[i][1], STDOUT_FILENO);
                close(pide_fd[i][1]);
                execlp("wc", "wc", "-l", NULL);
                _exit(1);
            }
        }
    }

}
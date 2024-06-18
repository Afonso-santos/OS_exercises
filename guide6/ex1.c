#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {

    int input_fd = open("/etc/passwd", O_RDONLY);
    int ouptut_fd = open("saida.txt", O_WRONLY | O_CREAT, 0644);
    int error_fd = open("erros.txt", O_WRONLY | O_CREAT, 0644);
    int  original = dup(STDOUT_FILENO);
    // sdtin(0)=> teclado
    // sdtout(1)=> monitor
    // stderr(2)=> monitor
    // input_fd => /etc/passwd
    //output_fd => saida.txt
    //error_fd => erros.txt

    dup2(input_fd, STDIN_FILENO);
    dup2(ouptut_fd, STDOUT_FILENO);
    dup2(error_fd, STDERR_FILENO);

    // sdtin(0)=> /etc/passwd
    // sdtout(1)=> saida.txt
    // stderr(2)=>  erros.txt
    // input_fd => /etc/passwd
    //output_fd => saida.txt
    //error_fd => erros.txt

    close(input_fd);
    close(ouptut_fd);
    close(error_fd);


    // write(original, "terminei\n", 9);
    // OR
    dup2(original, STDOUT_FILENO);
    write(STDOUT_FILENO, "terminei\n", 9);

    return 0;

}

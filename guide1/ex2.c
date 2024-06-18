#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
int main(int argc, char* argv[])
{
    char b[1];
    int i, o;


    // int from_fd =open(from_path, O_RDONLY);

    if ((i = open(argv[1], O_RDONLY)) == -1) {
        perror("erro na abertura do ficheiro de entrada ");
        return 1;
    }

    if ((o = open(argv[2], O_WRONLY | O_CREAT, 0640)) == -1) {
        perror("erro na abertura do ficheiro de saida");
        return 1;
    }

    while (read(i, &b, sizeof(char)) > 0) {
        write(o, &b, sizeof(char));
    }
    close(i);
    close(o);
    return 0;
}
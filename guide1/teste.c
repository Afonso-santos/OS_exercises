#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

// int open(const char *path, int oflag [, mode]);
// ssize_t read(int fildes, void *buf, size_t nbyte);
// ssize_t write(int fildes, const void *buf, size_t nbyte);
// off_t lseek(int fd, off_t offset, int whence);
// int close(int fildes);

/*
Implemente em C um programa mycat com funcionalidade similar ao comando cat, que le do seu
stdin e escreve para o seu stdout.
*/

int main(int argc, char *argv[])
{
    char b[1];

    while (read(0, &b, sizeof(char)) > 0){
        write(1, &b, sizeof(char));
    }
}

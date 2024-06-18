#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#define BUFFER_SIZE 1024

// int open(const char *path, int oflag [, mode]);
// ssize_t read(int fildes, void *buf, size_t nbyte);
// ssize_t write(int fildes, const void *buf, size_t nbyte);
// off_t lseek(int fd, off_t offset, int whence);
// int close(int fildes);

/*
Implemente em C um programa mycat com funcionalidade similar ao comando cat, que le do seu
stdin e escreve para o seu stdout.
*/

int main(int argc, char* argv[]) {
    char *buffer = (char *) malloc(sizeof(char)*BUFFER_SIZE);

    ssize_t write_bytes =0;
    ssize_t read_bytes=0;
    ssize_t bytes = 0;

    while ((bytes =read(0, buffer, BUFFER_SIZE))){
        read_bytes += bytes;
        write_bytes += write(1, buffer, bytes);
    }
    

    free(buffer);

    if((write_bytes-read_bytes)==0) return 0;

    return -1;
}

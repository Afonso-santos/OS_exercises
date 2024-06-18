#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int agrc, char* argv[]) {
    int fifo_fd=open("fifo", O_WRONLY);
    char buffer [10];
    int read_bytes=0;

    printf("Writing to fifo...\n");
    while((read_bytes=read(0, buffer, 10))>0) {
        write(fifo_fd, buffer, read_bytes);
    }
    close(fifo_fd);
    return 0;
}


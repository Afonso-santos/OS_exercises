#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int agrc, char* argv[]) {
    int fifo_fd = open("fifo", O_RDONLY);
    char buffer [10];
    int read_bytes = 0;
    printf("Reading from fifo...\n");
    while((read_bytes = read(fifo_fd, buffer, 10)) > 0) {
        write(1, buffer, read_bytes);
    } 
    close(fifo_fd);
    return 0;
    
}
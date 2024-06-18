#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int agrc, char* argv[]) {
    if (mkfifo("fifo", 0644)<0) {

        printf("Error creating fifo\n");       
    }
}
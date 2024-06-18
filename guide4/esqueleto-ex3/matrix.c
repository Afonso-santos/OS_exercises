#include "matrix.h"
#include <unistd.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int** createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int** matrix = (int**)malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int** matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void lookupNumber(int** matrix, int value, int* vector) {
    int pide_fd[2];
    pid_t pid;
    int  count = 0;
    int i, j;

    if (pipe(pide_fd) == -1) {
        perror("pipe");
        return;
    }

    for (i = 0;i < ROWS;i++) {
        if ((pid = fork()) == 0) {
            close(pide_fd[0]);
            for (j = 0;j < COLUMNS;j++) {
                if (matrix[i][j] == value) {
                    // printf("i = %d\n", i);
                    // printf("j = %d\n", j);
                    write(pide_fd[1], &j, sizeof(int));
                    break;
                }
            }
            if (j == COLUMNS) {
                write(pide_fd[1], &j, sizeof(int));
            }

            _exit(0);
        }
    }

    close(pide_fd[1]);

    while (read(pide_fd[0], &j, sizeof(int)) > 0) {
        if (j >= COLUMNS) {
            vector[count] = -1;
            count++;
        }
        else {
            vector[count] = j + 1;
            count++;
        }

    }

    for (i = 0;i < ROWS;i++) {
        wait(NULL);
    }

}




// if(pide_fd[2] == -1){
//     perror("pipe");
//     return;
// }
// if((pid=fork())==0){
//     close(pide_fd[0]);
//     for(i=0; i<ROWS; i++){
//         for(int j=0; j<COLUMNS; j++){
//             if(matrix[i][j] == value){
//                 write(pide_fd[1], &i, sizeof(int));
//                 // write(pide_fd[1], &j, sizeof(int));
//             }
//         }
//     }
//     _exit(0);
// }

// close(pide_fd[1]);


// for(i=0; read(pide_fd[0], &i, sizeof(int)) > 0; i++){
//     printf("i = %d\n", i);
//     vector[count] = i;
//     count++;
//     printf("data = %d\n", i);
// }



// wait(NULL);


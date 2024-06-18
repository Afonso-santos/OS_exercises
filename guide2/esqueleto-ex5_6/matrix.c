#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ex.5
int valueExists(int **matrix, int value) {
    pid_t pid;
    int status;
    pid_t wait_pid;
    int output=0;
    for( int i=0;i<ROWS;i++){
        if(fork()==0){
            for(int j=0;j<COLUMNS;j++){
                if(matrix[i][j]==value){
                    _exit(1);
                }
            }
            _exit(0);   
        }
    }
    for(int i=0;i<ROWS;i++){
        wait_pid=wait(&status);

        if(WIFEXITED(status)){
            if(WEXITSTATUS(status)==1){
                output=1;
            }
        }
    }


    return output;
}


// ex.6
void linesWithValue(int **matrix, int value) {
    pid_t pid;
    int status;
    pid_t wait_pid;
    pid_t pids[ROWS];
    for( int i=0;i<ROWS;i++){
        
    
        if((pid=fork())==0){
            for(int j=0;j<COLUMNS;j++){
                if(matrix[i][j]==value){
                    _exit(i+1);
                }
            }
            _exit(0);   
        }
        pids[i]=pid;
    }
    for(int i=0;i<ROWS;i++){
        wait_pid=waitpid(pids[i],&status,0);

        if(WIFEXITED(status)){

            if(WEXITSTATUS(status)!=0){

                
                printf("Line %d has the value %d\n",WEXITSTATUS(status)-1,value);
            }
            /**
             * else{
                printf("Line %d does not have the value %d\n",i,value);
                }
            */
        }else{
            printf("child process terminated abnormally\n");
        }
    }

}
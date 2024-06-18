#include "matrix.h"


int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);
 
    if(valueExists(matrix,4)){
        printf("Value exists\n");
    }else{
        printf("Value does not exist\n");
    }

    linesWithValue(matrix,4);


    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
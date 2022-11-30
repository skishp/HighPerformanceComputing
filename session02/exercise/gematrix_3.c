#include <stdio.h>
#include "gematrix.h"
#include "geutils.h"

/*exercise: 1. in main initialize a 7x8 row matrix A
            2. print matrix A
            3. Print the transposed matrix
            4. Print contet of the allocated memory block
            as a row vector of length m*n 
            5. Print the second row of the matrix
            6. print the third column of the matrix
            7. Print the following 2x3 matrix
                A_1 = [a_24,a_25,a_26;a_34,a_35,a_36]
            8. Print the following 2x3 matrix
                A_2 = [a_36,a_35,a_34;a_26,a_25,a_24]*/

int main(void){
    struct GeMatrix A = allocateGeMatrix(7,8, RowMajor);
    geinit(A.numRows, A.numCols, A.data, A.incRow, A.incCols);
    printf("A= \n");
    geprint(A.numRows, A.numCols, A.data, A.incRow, A.incCols);

    printf("\n A^t = \n");
    geprint(A.numCols,A.numRows,A.data,A.incCols,A.incRow);

    printf("\n A.data = \n");
    geprint(1, A.numCols*A.numRows, A.data, 1,1);

    printf("\n A[2,:]  = \n");
    geprint(1,A.numCols,A.data + 1*A.incRow, A.incRow,A.incCols);

    printf("\n A[:,3] = \n");
    geprint(A.numRows,1,A.data + 2*A.incCols,A.incRow, A.incCols);

    printf("\n A_1 = \n");
    geprint(2,3,A.data + 1*A.incRow+2*A.incCols,A.incRow,A.incCols);

    printf("\n A_2 = \n");
    geprint(2,3,A.data + 2*A.incRow+4*A.incCols,-A.incRow,-A.incCols);

    releaseGeMatrix(&A);
}
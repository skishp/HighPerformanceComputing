#include <stddef.h>
#include <stdio.h> 

#include "gematrix.h"
#include "geutils.h"

/*Write a simple test file that allocates 7x8 matrix and then initalizs it as follows:
1. first three rows with geinit
2. first two rows with geinint Nan
3. the last two rows with geinit Ran
exercise:   1. write a function which calculates the inf norm of matrices
            2. allocate 7x7 matrix A which gets initialized with geinit
            3. Compute InfNorm(A - A)
            4. Compute InfNorm(A - A^T)
*/

int main(void){
    struct GeMatrix A = allocateGeMatrix(7,8,ColMajor);
    geinitNan(A.numRow, A.numCol, A.data, A.incRow, A.incCol);
    geinit(3,A.numCol,A.data,A.incRow,A.incCol);
    geinitRand(2,A.numCol,A.data + (A.numRow -2)*A.incRow,A.incRow,A.incCol);
    printf("A = \n");
    geprint(A.numRow,A.numCol,A.data,A.incRow,A.incCol);
    freeGeMatrix(&A);

    A = allocateGeMatrix(7,7,ColMajor);
    geinit(A.numRow,A.numCol,A.data,A.incRow,A.incCol);
    printf("new init A = \n");
    geprint(A.numRow,A.numCol,A.data,A.incRow,A.incCol);
    double a = gediffNrmInf(A.numRow,A.numCol,A.data,A.incRow,A.incCol,A.data,A.incRow,A.incCol);
    printf("\nsupnorm(A-A) = %4.1lf\n",a);
    double b = gediffNrmInf(A.numRow,A.numCol,A.data,A.incRow,A.incCol,A.data,A.incCol,A.incRow);
    printf("supnorm(A-A^T) = %4.1lf\n",b);
    freeGeMatrix(&A);
}
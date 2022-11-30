#include <stdio.h>
#include "gematrix.h"
#include "geutils.h"

/*exercise:provide in geutils.c implementations for the functions
           declared in geutils.h. */

int main(void){
    struct GeMatrix A = allocateGeMatrix(7,8, ColMajor);
    geinit(A.numRows, A.numCols, A.data, A.incRow, A.incCols);
    printf("A = \n");
    geprint(A.numRows, A.numCols, A.data, A.incRow, A.incCols);

    releaseGeMatrix(&A);
}
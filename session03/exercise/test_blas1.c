#include <stdio.h>
#include <stdlib.h>
#include "blas1.h"
#include "gematrix.h"
#include "geutils.h"

#ifndef SEED
#define SEED 42
#endif // SEED

int
main(void)
{
    printf("using seed = %u\n", SEED);
    srand(SEED);

    struct GeMatrix A = allocateGeMatrix(7, 8, ColMajor);

    geinit(3, A.numCol, A.data, A.incRow, A.incCol);
    geinitNan(2, A.numCol, &A.data[3 * A.incRow], A.incRow, A.incCol);
    geinitRand(2, A.numCol, &A.data[5 * A.incRow], A.incRow, A.incCol);

    printf("A =\n");
    geprint(A.numRow, A.numCol, A.data, A.incRow, A.incCol);

    printf("scale A(0,:) with 42\n");
    dscal(A.numCol, 42, A.data, A.incCol);

    printf("A =\n");
    geprint(A.numRow, A.numCol, A.data, A.incRow, A.incCol);

    printf("scale A(3,:) with 0\n");
    dscal(A.numCol, 0, &A.data[3 * A.incRow], A.incCol);

    printf("A =\n");
    geprint(A.numRow, A.numCol, A.data, A.incRow, A.incCol);

    printf("swap A(1,:) and A(2,:)\n");
    dswap(A.numCol,
          &A.data[1 * A.incRow], A.incCol,
          &A.data[2 * A.incRow], A.incCol);

    printf("A =\n");
    geprint(A.numRow, A.numCol, A.data, A.incRow, A.incCol);

    printf("A(1,:) <- 2 * A(2,:) + A(1,:)\n");
    daxpy(A.numCol,
          2,
          &A.data[2 * A.incRow], A.incCol,
          &A.data[1 * A.incRow], A.incCol);

    printf("A =\n");
    geprint(A.numRow, A.numCol, A.data, A.incRow, A.incCol);

    printf("iamax(A(5,:)) = %zu\n",
           iamax(A.numCol, &A.data[5 * A.incRow], A.incCol));

    printf("iamax(A(:,5)) = %zu\n",
           iamax(A.numRow, &A.data[5 * A.incCol], A.incRow));

    freeGeMatrix(&A);

    freeGeMatrix(&A);
}
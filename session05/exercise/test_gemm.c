#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "gematrix.h"
#include "geutils.h"
#include "blas3.h"

#ifndef ALPHA
#define ALPHA 1.5
#endif // ALPHA

#ifndef BETA
#define BETA 1
#endif // ALPHA

void init(struct GeMatrix A, bool withNan)
{
    if (!withNan)
    {
        geinitRand(A.numRows, A.numCols, A.data, A.incRow, A.incCol);
    }
    else
    {
        geinitNan(A.numRows, A.numCols, A.data, A.incRow, A.incCol);
    }
}

void test(double alpha, struct GeMatrix A, struct GeMatrix B,
          double beta, struct GeMatrix C,
          void dgemm())
{
    assert(A.numCols == B.numRows);
    dgemm(C.numRows, C.numCols, A.numCols,
          alpha,
          A.data, A.incRow, A.incCol,
          B.data, B.incRow, B.incCol,
          beta,
          C.data, C.incRow, C.incCol);
}

int main(void)
{
    struct GeMatrix A = allocateGeMatrix(3, 4, RowMajor);
    struct GeMatrix B = allocateGeMatrix(4, 5, RowMajor);
    struct GeMatrix C = allocateGeMatrix(3, 5, RowMajor);

    init(A, false);
    init(B, false);
    init(C, BETA == 0);

    printf("A =\n");
    geprint(A.numRows, A.numCols, A.data, A.incRow, A.incCol);
    printf("B =\n");
    geprint(B.numRows, B.numCols, B.data, B.incRow, B.incCol);
    printf("C =\n");
    geprint(C.numRows, C.numCols, C.data, C.incRow, C.incCol);

    printf("computing: C <- %4.2lf * C + %4.2lf * A * B\n",
           (double)BETA, (double)ALPHA);
    test(ALPHA, A, B, BETA, C, dgemm_ijl);

    printf("C =\n");
    geprint(C.numRows, C.numCols, C.data, C.incRow, C.incCol);

    printf("using different order in the for loops:\n");
    printf("computing: C <- %4.2lf * C + %4.2lf * A * B\n",
           (double)BETA, (double)ALPHA);
    test(ALPHA, A, B, BETA, C, dgemm_ilj);
    printf("C = \n");
    geprint(C.numRows, C.numCols, C.data, C.incRow, C.incCol);
    releaseGeMatrix(&A);
    releaseGeMatrix(&B);
    releaseGeMatrix(&C);
}
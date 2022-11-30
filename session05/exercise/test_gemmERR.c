#include <assert.h>
#include <float.h>
#include <math.h>
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

void
init(struct GeMatrix A, bool withNan)
{
    if (!withNan) {
        geinitRand(A.numRows, A.numCols, A.data, A.incRow, A.incCol);
    } else {
        geinitNan(A.numRows, A.numCols, A.data, A.incRow, A.incCol);
    }
}

void
test(double alpha, struct GeMatrix A, struct GeMatrix B,
     double beta, struct GeMatrix C0, struct GeMatrix C,
     void dgemm())
{
    assert(C0.numRows == C.numRows && C0.numCols == C.numCols);
    dgecopy(C.numRows, C.numCols,
            C0.data, C0.incRow, C0.incCol,
            C.data, C.incRow, C.incCol);

    assert(A.numCols == B.numRows);
    dgemm(C.numRows, C.numCols, A.numCols,
          alpha,
          A.data, A.incRow, A.incCol,
          B.data, B.incRow, B.incCol,
          beta,
          C.data, C.incRow, C.incCol);
}

size_t
max_(size_t a, size_t b)
{
    return a > b ? a : b;
}

double gemmErr(double alpha, struct GeMatrix A, struct GeMatrix B,
               struct GeMatrix C0, double beta, struct GeMatrix Cref,
               struct GeMatrix Ctst)
{
    assert(C0.numRows == Cref.numRows && C0.numCols == Cref.numCols);
    assert(C0.numRows == Ctst.numRows && C0.numCols == Ctst.numCols);
    assert(A.numCols == B.numRows);

    size_t m = C0.numRows;
    size_t n = C0.numRows;
    size_t k = A.numCols;

    double normD = gediffNrmInf(m, n,
                                Cref.data, Cref.incRow, Cref.incCol,
                                Ctst.data, Ctst.incRow, Ctst.incCol);
    double normC0 = dgenrm_inf(m, n, C0.data, C0.incRow, C0.incCol);
    double normA  = dgenrm_inf(m, k, A.data, A.incRow, A.incCol);
    double normB  = dgenrm_inf(k, n, B.data, B.incRow, B.incCol);
    size_t N      = max_(m, max_(n, k));

    normA  *= fabs(alpha);
    normC0 *= fabs(beta);

    return normD/(DBL_EPSILON*(N*normA*normB+normC0));
}

int
main(void)
{
    struct GeMatrix A = allocateGeMatrix(300, 400, RowMajor);
    struct GeMatrix B = allocateGeMatrix(400, 500, RowMajor);
    struct GeMatrix C0 = allocateGeMatrix(300, 500, RowMajor);

    init(A, false);
    init(B, false);
    init(C0, BETA == 0);

    // Cref will be overwritten with dgemm_ijl
    struct GeMatrix Cref = allocateGeMatrix(C0.numRows, C0.numCols, RowMajor);
    test(ALPHA, A, B, BETA, C0, Cref, dgemm_ijl);

    // Ctst will be overwritten with dgemm_ijl
    struct GeMatrix Ctst = allocateGeMatrix(C0.numRows, C0.numCols, RowMajor);
    test(ALPHA, A, B, BETA, C0, Ctst, dgemm_ilj);

    // compare Cref and Ctst
    printf("error = %4.5e\n",
           gemmErr(ALPHA, A, B, C0, BETA, Cref, Ctst));

    releaseGeMatrix(&A);
    releaseGeMatrix(&B);
    releaseGeMatrix(&C0);
    releaseGeMatrix(&Cref);
    releaseGeMatrix(&Ctst);
}
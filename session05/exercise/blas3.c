#include <math.h>

#include "blas3.h"
/*
implementation of the GEMM algorithm
1. declare function which scales matrices
2. function for matrix multiplication
*/

ptrdiff_t abs_(ptrdiff_t x)
{
    return x > 0 ? x : -x;
}

/*
dgescal is a function to scale a Matrix A with faktor Alpha, Nan entries are allowed
notice: simple cache optimization, by checking dimensions
*/

void dgescal(size_t m, size_t n,
             double alpha,
             double *A, ptrdiff_t incRow, ptrdiff_t incCol)
{
    if (abs_(incRow) < abs_(incCol))
    {
        // col major: scale A^T
        dgescal(n, m, alpha, A, incCol, incRow);
        return;
    }
    // only handle row major case
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (alpha != 0)
            {
                A[i * incRow + j * incCol] *= alpha;
            }
            else
            {
                A[i * incRow + j * incCol] = 0;
            }
        }
    }
}

double
dgenrm_inf(size_t m, size_t n,
           double *A, ptrdiff_t incRow, ptrdiff_t incCol)
{
    double res = 0;
    for (size_t i = 0; i < m; ++i)
    {
        double diff = 0;
        for (size_t j = 0; j < n; ++j)
        {
            diff += fabs(A[i * incRow + j * incCol]);
        }
        if (diff > res)
        {
            res = diff;
        }
    }
    return res;
}

void dgecopy(size_t m, size_t n,
             const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
             double *B, ptrdiff_t incRowB, ptrdiff_t incColB)
{
    if (abs_(incRowB) > abs_(incColB))
    {
        dgecopy(n, m, A, incColA, incRowA, B, incColB, incRowB);
        return;
    }
    // B is col major:
    for (size_t j = 0; j < n; ++j)
    {
        for (size_t i = 0; i < m; ++i)
        {
            B[i * incRowB + j * incColB] = A[i * incRowA + j * incColA];
        }
    }
}

void dgeaxpy(size_t m, size_t n, double alpha,
             const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
             double *B, ptrdiff_t incRowB, ptrdiff_t incColB)
{
    if (abs_(incRowB) > abs_(incColB))
    {
        dgeaxpy(n, m, alpha, A, incColA, incRowA, B, incColB, incRowB);
        return;
    }
    // B is col major:
    for (size_t j = 0; j < n; ++j)
    {
        for (size_t i = 0; i < m; ++i)
        {
            B[i * incRowB + j * incColB] += alpha * A[i * incRowA + j * incColA];
        }
    }
}

void dgemm_ijl(size_t m, size_t n, size_t k,
               double alpha,
               const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
               const double *B, ptrdiff_t incRowB, ptrdiff_t incColB,
               double beta,
               double *C, ptrdiff_t incRowC, ptrdiff_t incColC)
{
    dgescal(m, n, beta, C, incRowC, incColC);
    if (alpha == 0 || k == 0)
    {
        return;
    }
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            for (size_t l = 0; l < k; ++l)
            {
                C[i * incRowC + j * incColC] += alpha *
                                                A[i * incRowA + l * incColA] *
                                                B[l * incRowB + j * incColB];
            }
        }
    }
}

void dgemm_ilj(size_t m, size_t n, size_t k,
               double alpha,
               const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
               const double *B, ptrdiff_t incRowB, ptrdiff_t incColB,
               double beta,
               double *C, ptrdiff_t incRowC, ptrdiff_t incColC)
{
    dgescal(m, n, beta, C, incRowC, incColC);
    if (alpha == 0 || k == 0)
    {
        return;
    }
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t l = 0; l < k; ++l)
        {
            for (size_t j = 0; j < n; ++j)
            {
                C[i * incRowC + j * incColC] += alpha *
                                                A[i * incRowA + l * incColA] *
                                                B[l * incRowB + j * incColB];
            }
        }
    }
}
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "blockMatrixBlas3.h"

ptrdiff_t
abs_(ptrdiff_t x)
{
    return x > 0 ? x : -x;
}

void
dgescal(size_t m, size_t n,
        double alpha,
        double *A, ptrdiff_t incRow, ptrdiff_t incCol)
{
    if (abs_(incRow) < abs_(incCol)) {
        // col major: scale A^T
        dgescal(n, m, alpha, A, incCol, incRow);
        return;
    }
    // only handle row major case
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (alpha != 0) {
                A[i * incRow + j * incCol] *= alpha;
            } else {
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
    for (size_t i = 0; i < m; ++i) {
        double diff = 0;
        for (size_t j = 0; j < n; ++j) {
            diff += fabs(A[i * incRow + j * incCol]);
        }
        if (diff > res) {
            res = diff;
        }
    }
    return res;
}


void
dgecopy(size_t m, size_t n,
        const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
        double *B, ptrdiff_t incRowB, ptrdiff_t incColB)
{
    if (abs_(incRowB) > abs_(incColB)) {
        dgecopy(n, m, A, incColA, incRowA, B, incColB, incRowB);
        return;
    }
    // B is col major:
    for (size_t j=0; j<n; ++j) {
        for (size_t i=0; i<m; ++i) {
            B[i*incRowB+j*incColB] = A[i*incRowA+j*incColA];
        }
    }
}

void
dgeaxpy(size_t m, size_t n, double alpha,
        const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
        double *B, ptrdiff_t incRowB, ptrdiff_t incColB)
{
    if (abs_(incRowB) > abs_(incColB)) {
        dgeaxpy(n, m, alpha, A, incColA, incRowA, B, incColB, incRowB);
        return;
    }
    // B is col major:
    for (size_t j=0; j<n; ++j) {
        for (size_t i=0; i<m; ++i) {
            B[i*incRowB+j*incColB] += alpha*A[i*incRowA+j*incColA];
        }
    }
}

#ifndef M_C
#define M_C 8
#endif

#ifndef K_C
#define K_C 256
#endif

#ifndef N_C
#define N_C 128
#endif


void
dgemm_cache(size_t m, size_t n, size_t k,
            double alpha,
            const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
            const double *B, ptrdiff_t incRowB, ptrdiff_t incColB,
            double beta,
            double *C, ptrdiff_t incRowC, ptrdiff_t incColC)
{
    if (m==0 || n==0) {
        return;
    }
    dgescal(m, n, beta, C, incRowC, incColC);

    if (k==0 || alpha==0) {
        return;
    }

    size_t mb = (m + M_C -1) / M_C;
    size_t nb = (n + N_C -1) / N_C;
    size_t kb = (k + K_C -1) / K_C;

    size_t mr = m % M_C;
    size_t nr = n % N_C;
    size_t kr = k % K_C;

    double *A_ = malloc(M_C * K_C * sizeof(double));
    double *B_ = malloc(K_C * N_C * sizeof(double));
    double *C_ = malloc(M_C * N_C * sizeof(double));

    if (!A_ || !B_ || !C_) {
        free(A_);
        free(B_);
        free(C_);
        fprintf(stderr, "malloc failed\n");
        abort();
        return;
    }

    for (size_t jb=0; jb<nb; ++jb) {
        size_t N = (jb!=nb-1 || nr==0) ? N_C
                                       : nr;

        for (size_t lb=0; lb<kb; ++lb) {
            size_t K = (lb!=kb-1 || kr==0) ? K_C
                                           : kr;

            dgecopy(K, N,
                    &B[lb*K_C*incRowB + jb*N_C*incColB], incRowB, incColB,
                    B_, N_C, 1);

            for (size_t ib=0; ib<mb; ++ib) {
                size_t M = (ib!=mb-1 || mr==0) ? M_C
                                               : mr;

                dgecopy(M, K,
                        &A[ib*M_C*incRowA + lb*K_C*incColA], incRowA, incColA,
                        A_, K_C, 1);

                dgemm_ilj(M, N, K,
                          alpha,
                          A_, K_C, 1,
                          B_, N_C, 1,
                          0.0,
                          C_, N_C, 1);

                dgeaxpy(M, N, 1.0,
                        C_, N_C, 1,
                        &C[ib*M_C*incRowC + jb*N_C*incColC], incRowC, incColC);
            }
        }
    }

    free(A_);
    free(B_);
    free(C_);
} 
#ifndef BLOCKMATRIXBLAS3_H
#define BLOCKMATRIXBLAS3_H

#include <stddef.h>

void dgescal(size_t m, size_t n,
             double alpha,
             double *A, ptrdiff_t incRow, ptrdiff_t incCol);

double dgenrm_inf(size_t m, size_t n,
                  double *A, ptrdiff_t incRow, ptrdiff_t incCol);

void dgecopy(size_t m, size_t n,
             const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
             double *B, ptrdiff_t incRowB, ptrdiff_t incColB);

void dgeaxpy(size_t m, size_t n, double alpha,
             const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
             double *B, ptrdiff_t incRowB, ptrdiff_t incColB);

void dgemm_ijl(size_t m, size_t n, size_t k, double alpha,
               const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
               const double *B, ptrdiff_t incRowB, ptrdiff_t incColB,
               double beta,
               double *C, ptrdiff_t incRowC, ptrdiff_t incColC);

void dgemm_ilj(size_t m, size_t n, size_t k, double alpha,
               const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
               const double *B, ptrdiff_t incRowB, ptrdiff_t incColB,
               double beta,
               double *C, ptrdiff_t incRowC, ptrdiff_t incColC);

void
dgemm_cache(size_t m, size_t n, size_t k,
            double alpha,
            const double *A, ptrdiff_t incRowA, ptrdiff_t incColA,
            const double *B, ptrdiff_t incRowB, ptrdiff_t incColB,
            double beta,
            double *C, ptrdiff_t incRowC, ptrdiff_t incColC);


#endif // BLAS3_H
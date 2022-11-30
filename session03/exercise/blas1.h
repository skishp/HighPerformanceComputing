#ifndef BLAS1_H
#define BLAS1_H

#include <stddef.h>

void dscal(size_t n, double alpha, double *x, ptrdiff_t incX);

void dswap(size_t n, double *x, ptrdiff_t incX, double *y, ptrdiff_t incY);

void daxpy(size_t n, double alpha, const double *x, ptrdiff_t incX, double *y, ptrdiff_t incY);

size_t iamax(size_t n, const double *x, ptrdiff_t incX);
#endif
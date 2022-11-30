#ifndef GEUTILS_h
#define GEUTILS_h

#include <stddef.h>
#include <assert.h>


void geinit(size_t m, size_t n, double *A, ptrdiff_t incRow, ptrdiff_t incCol);

void geinitNan(size_t m, size_t n, double *A, ptrdiff_t incRow, ptrdiff_t incCol);

void geinitRand(size_t m, size_t n, double *A, ptrdiff_t incRow, ptrdiff_t incCol);

void geprint(size_t m, size_t n, double *A, ptrdiff_t incRow, ptrdiff_t incCol);

double gediffNrmInf(size_t m, size_t n, const double *A, ptrdiff_t incRow, ptrdiff_t incCol,
                     const double *B, ptrdiff_t incRowB, ptrdiff_t incColB);

double walltime(void);

#endif
#ifndef GEUTILS_H
#define GEUTILS_H

#include <stddef.h>

void geinit(size_t m, size_t n, double *A, 
            ptrdiff_t incRow, ptrdiff_t incCol);
void geprint(size_t m, size_t n, const double *A,
            ptrdiff_t incRow, ptrdiff_t incCol);

#endif
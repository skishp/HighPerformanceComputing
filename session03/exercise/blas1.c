#include <math.h>

#include "blas1.h"

// x <- alpha * x
void
dscal(size_t n, double alpha, double *x, ptrdiff_t incX)
{
    if (alpha == 1) {
        return;
    }
    if (alpha == 0) {
        for (size_t j = 0; j < n; ++j) {
            x[j * incX] = 0;
        }
    } else {
        for (size_t j = 0; j < n; ++j) {
            x[j * incX] *= alpha;
        }
    }
}

// x <-> y
void
dswap(size_t n, double *x, ptrdiff_t incX, double *y, ptrdiff_t incY)
{
    for (size_t j = 0; j < n; ++j) {
        double tmp = x[j * incX];
        x[j * incX] = y[j * incY];
        y[j * incY] = tmp;
    }
}

// y <- alpha * x + y
void
daxpy(size_t n, double alpha, const double *x, ptrdiff_t incX,
      double *y, ptrdiff_t incY)
{
    for (size_t j = 0; j < n; ++j) {
        y[j * incY] += alpha * x[j * incX];
    }
}

// return max_j |x_j|
size_t
iamax(size_t n, const double *x, ptrdiff_t incX)
{
    double amax = 0;
    size_t index = 0;
    for (size_t j = 0; j < n; ++j) {
        if (fabs(x[j * incX]) > amax) {
            amax = fabs(x[j * incX]);
            index = j;
        } else if (isnan(fabs(x[j * incX]))) {
            // handle NaN cases: this is not specified in BLAS but common
            // practise suggests to return the index of the first NaN
            return j;
        }
    }
    return index;
}
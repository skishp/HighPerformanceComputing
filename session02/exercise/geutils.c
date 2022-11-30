#include <stdio.h>

#include "geutils.h"

void geinit(size_t m , size_t n, double *A, ptrdiff_t incRow,
            ptrdiff_t incCol){
    for(size_t i = 0;i<m;++i){
        for(size_t j = 0; j<n;++j){
            A[i*incRow + j*incCol] = i*n + j+1;
        }
    }
}

void geprint(size_t m, size_t n, const double *A,
            ptrdiff_t incRow, ptrdiff_t incCol){
    for(size_t i = 0; i<m; ++i){
        for(size_t j = 0; j<n; ++j){
            printf(" %4.1lf",A[i*incRow + j*incCol]);
        }
        printf("\n");
    }
}
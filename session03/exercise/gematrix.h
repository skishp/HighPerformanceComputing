#ifndef GEMATRIX_H
#define GEMATRIX_h
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct GeMatrix
{
    size_t numRow, numCol;
    double *data;
    ptrdiff_t incRow, incCol;
};

enum StorageOrder{RowMajor, ColMajor};

struct GeMatrix allocateGeMatrix(size_t m,size_t n,enum StorageOrder order);
void freeGeMatrix(struct GeMatrix *A);

#endif
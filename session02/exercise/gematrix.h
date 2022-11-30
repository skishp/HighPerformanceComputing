#ifndef GEMATRIX_h
#define GEMATRIX_h

#include <stddef.h>
/*exercise: write "FirstStepsWithMatrices" again but with a 
            header file and implement the fuction allocate-
            GeMatrix and releaseGeMatrix in a c file.*/
struct GeMatrix
{
    size_t numRows, numCols;
    double *data;
    ptrdiff_t incRow, incCols;
};

enum StorageOrder{ RowMajor, ColMajor};

struct GeMatrix allocateGeMatrix(size_t m, size_t n, enum StorageOrder order);
void releaseGeMatrix(struct GeMatrix *A);

#endif 
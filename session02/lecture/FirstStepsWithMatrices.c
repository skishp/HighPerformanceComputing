#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct GeMatrix{
    size_t numRows, numCols;
    double *data;
    ptrdiff_t incRow, incCol;

};

int main(){
    struct GeMatrix A; 
    A.numCols = 6;
    A.numRows = 3;
    A.data = malloc(A.numRows * A.numCols * sizeof(double));
    A.incRow = 1;
    A.incCol = A.numRows;

    /*check if malloc went through successfully*/
    if(!A.data){
        fprintf(stderr, "matrix allocation: out of memory");
        exit(1);
    }
    free(A.data);
}
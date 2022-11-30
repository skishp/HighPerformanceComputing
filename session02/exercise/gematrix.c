#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "gematrix.h"


struct GeMatrix allocateGeMatrix(size_t m, size_t n, enum StorageOrder order){
    struct GeMatrix A = {m,n,malloc(m*n*sizeof(double)),
                        order == RowMajor ? n : 1,
                        order == RowMajor ? 1 : m
    };
    /*check if mallow went through*/
    if(!A.data){
        printf("matrix allocation: out of memory");
        exit(1);
    }
    return A;
}

void releaseGeMatrix(struct GeMatrix *A){
    /*check if A is 0*/
    assert(A);
    free(A -> data);
}

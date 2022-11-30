#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*y <- y+alhpa x*/

void axpy(size_t n, double alpha, const double* x, ptrdiff_t incX, double* y, ptrdiff_t incY){
    if(!alpha){
        return;
    }
    for(size_t i=0;i<n;++i){
        y[i*incY] += alpha * x[i*incX];
    }
}

void init_vector(size_t n, double* x, ptrdiff_t incX){
    for(size_t i=0;i<n;++i){
        x[i*incX] = i +1;
    }
}

void print_vector(size_t n, const double* x, ptrdiff_t incX){
    for(size_t i = 0; i<n; ++i){
        printf(" %.2lf", x[i*incX]);
    }
}

int main(){
    const size_t n = 8;
    double* x = malloc(n*sizeof(double));
    init_vector(n,x,1);
    double* y = malloc(n*sizeof(double));
    init_vector(n,y,1);
    axpy(n,3.0,x,1,y,1);
    print_vector(n,y,1); printf("\n");
    free(x),free(y);
}
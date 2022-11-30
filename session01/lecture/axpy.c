#include <stddef.h>
#include <stdio.h>

/*y <-y + alhpa x */
void axpy(size_t n, double alpha, const double* x, ptrdiff_t incX, double* y, ptrdiff_t incY){
    if(!alpha){
        return;
    }
    for(size_t i = 0; i<n; ++i){
        y[i*incY] += alpha*x[i*incX];
    }
}

int main(){
    double A[] = {1,2,3,4,5,6}; //2x3 matrix
    const size_t m = 2,n=3;
    double* y = A + 1; double* x = A + 2;
    axpy(m,2.0,x,n,y,n);

    for(size_t i = 0; i < m; ++i){
        printf(" %lf",y[i*n]);
    } 
    printf("\n");
}
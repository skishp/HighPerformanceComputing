#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

#include "geutils.h"

void geinitNan(size_t m, size_t n, double *A, ptrdiff_t incRow, ptrdiff_t incCol){
    for(size_t i = 0;i<m;++i){
        for(size_t j = 0; j < n; ++j){
            A[i*incRow + j*incCol] = nan("");
        }
    }
}

void geinit(size_t m, size_t n, double *A, ptrdiff_t incRow, ptrdiff_t incCol){
    for(size_t i = 0; i<m;++i){
        for(size_t j = 0; j<n; ++j){
            A[i*incRow + j*incCol] = i*n + j+1;
        }
    }
}
#ifndef SEED
#define SEED 42 
#endif
void geinitRand(size_t m, size_t n, double *A, ptrdiff_t incRow, ptrdiff_t incCol){
    srand(SEED);
    printf("Seed = %u\n", SEED);
    for(size_t i = 0; i<m;++i){
        for(size_t j = 0; j<n;++j){
            A[i*incRow + j*incCol] = ((double)rand()*2/(double)RAND_MAX -1);
        }
    }
}


void geprint(size_t m, size_t n, double *A, ptrdiff_t incRow, ptrdiff_t incCol){
    for(size_t i = 0; i<m; ++i){
        for(size_t j = 0; j<n; ++j){
            printf(" %4.1lf",A[i*incRow + j*incCol]);
        }
        printf("\n");
    }
}

double gediffNrmInf(size_t m, size_t n, const double *A, ptrdiff_t incRow, ptrdiff_t incCol,
                     const double *B, ptrdiff_t incRowB, ptrdiff_t incColB){
    double counter = 0;
    for(size_t i = 0; i<m;++i){
        double counter_current = 0;
        for(size_t j = 0; j<n; ++j){
            counter_current += abs(A[i*incRow + j*incCol] - B[i*incRowB + j*incColB]);
        }
        if(counter_current>counter){
            counter = counter_current;
        }
    }
    return counter;
}

double walltime(void){
    static clock_t ticks_per_second = 0;
    if(!ticks_per_second){
        ticks_per_second = sysconf(_SC_CLK_TCK);
    }
    struct tms timebuff;
    return (double)times(&timebuff) /ticks_per_second;
}
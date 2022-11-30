#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "gematrix.h"
#include "geutils.h"

#ifndef MINDIM_M
#define MINDIM_M 3000
#endif

#ifndef INC_M
#define INC_M 100
#endif

#ifndef MAXDIM_M
#define MAXDIM_M 7000
#endif

#ifndef MINDIM_N
#define MINDIM_N 3000
#endif

#ifndef INC_N
#define INC_N 100
#endif

#ifndef MAXDIM_N
#define MAXDIM_N 7000
#endif

#ifndef MIN_T
#define MIN_T 4
#endif

int main(void){
    printf("    M   N   t0  t1  t1/t0   diff\n");
    printf("            row-maj col-maj\n");
    printf("===============================\n");
    for(size_t m = MINDIM_M,n = MINDIM_N;m<=MAXDIM_M && n<=MAXDIM_N;m+=INC_M, n+=INC_N){
        //bench initializiation of a row-major matrix
        struct GeMatrix RM = allocateGeMatrix(m,n,RowMajor);
        double t0 = 0;
        size_t runs0 = 0;
        while(t0 <= MIN_T){
            double t = walltime();
            geinit(RM.numRow,RM.numCol,RM.data,RM.incRow,RM.incCol);
            t0 += walltime() - t;
            ++runs0;
        }
        t0/=runs0;

        //bench initialization of a col-major matrix
        struct GeMatrix CM = allocateGeMatrix(m,n,ColMajor);
        double t1 = 0; 
        size_t runs1 = 0;
        while(t1<=MIN_T){
            double t  = walltime();
            geinit(CM.numRow,CM.numCol,CM.data,CM.incRow,CM.incCol);
            t1 += walltime() - t;
            ++runs1;
        }
        t1 /=runs1;

        //compute: diff = ||RM - CM||_inf
        assert(RM.numRow == CM.numRow);
        assert(RM.numCol == CM.numCol);
        double diff = gediffNrmInf(RM.numRow,RM.numCol,RM.data,RM.incRow,RM.incCol,CM.data,CM.incRow,CM.incCol);
        printf("%4zd %4zd %7.2lf %7.2lf %7.2lf %10.2le\n", m,n,t0,t1,t1/t0,diff);

        freeGeMatrix(&RM);
        freeGeMatrix(&CM);

    }

}
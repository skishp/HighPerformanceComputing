#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <stddef.h>

/*exercise: 1. allocate two big vecotrs twice as large as the
            lenght using malloc with pointers vector1 and 
            vector 2 pointing to it.
            2. using the array behind vector1 to store two vectors
            of the given length consecutively
            3. using the array behind vector2 to store two inter-
            leaving vectors of the given length.
            4. releasing the arrays behind vector1 and vector2 
            with free*/

double walltime(){
    static clock_t ticks_per_second = 0;
    if(!ticks_per_second){
        ticks_per_second = sysconf(_SC_CLK_TCK);
    }
    struct tms timebuff;

    return (double) times(&timebuff) / ticks_per_second;
}

void init_vector(size_t len, double * v, ptrdiff_t incr){
    for(size_t i = 0; i<len; ++i){
        v[i*incr] = i + incr;
    }
}

#define MAX_len 134217728
int main(){
    printf("    len t1 (seperate) t2 (interleaving)     t2/t1\n");
    for(size_t i = 8192; i<MAX_len/2; i*=2){
        printf("%8zu", i);

        double* v = malloc(sizeof(double) * i *2);
        double* x = v;
        double* y = v + i;
        double t0 = walltime();
        init_vector(i,x,1);
        init_vector(i,y,1);
        double t1 = walltime() - t0;
        printf(" %12.2lf", t1);

        double* v2 = malloc(sizeof(double) * i * 2);
        x = v2; y = v2+1;
        t0 = walltime();
        init_vector(i,x,2);
        init_vector(i,y,2);
        double t2 = walltime() - t0;
        printf(" %12.2lf %16.2lf",t2, t2/t1);

        printf("\n");
        free(v); free(v2);
    }
}
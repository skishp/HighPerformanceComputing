#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*Exercise: Rewrite your solution to "FirstStepsWithC" to
            allow for a dynamic array length which is read
            from standard input.*/

void init_vector(size_t s, double* v,ptrdiff_t incr){
    for(size_t i = 0; i<s; ++i){
        v[i*incr] = i + 1;
    }
}

void print_vector(size_t s, double* v, ptrdiff_t incr){
    for(size_t i = 0; i<s; ++i){
        printf("%4.1lf",v[i*incr]);
    }
}


int main(){
    printf("vector length = ");
    size_t max_size;
    if(scanf("%zu", &max_size) !=1) return 1;
    printf("\n Ok, vector length = %zu \n", max_size);
    double *vector = malloc(sizeof(double)*max_size);
    if(!vector){
        printf("unable to allocate heap memory for %zu double values\n", max_size);
        return 1;
    }

    double *x = vector;
    printf("initialize x as one vector\n");
    init_vector(max_size, x, 1);
    printf("vector =");
    print_vector(max_size, x, 1);

    printf("\nusing space for two vectors of length 4\n");
    size_t size = max_size/2;
    /*create pointer which points to x+4*/
    double *y = vector + size;
    init_vector(size, x, 1);
    printf("x = "); print_vector(size,x,1);
    init_vector(size,y,1);
    printf("\ny = "); print_vector(size,y,1);
    printf("\n vector = "); print_vector(max_size,vector,1);

    printf("\nusing the space for two interleaving vectors\n");
    y = vector + 1; 
    init_vector(size,x,2); init_vector(size,y,2);
    printf("x = ");print_vector(size,x,2);
    printf("\ny = ");print_vector(size,y,2);
    printf("\nvector = "); print_vector(max_size, vector,1);

    free(vector);
    
}
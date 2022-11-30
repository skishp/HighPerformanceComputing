#include <stdio.h>
#include <stddef.h>


/*exercise: 1. A function init_vector shall initialize a vector. The
            cetor is specified by a pointer to its first element, the
            number of elements, and the stride between to consecutive
            elements of the vector. The first element of the vector is
            to be initialized to 1, the second to 2 etc
            
            2. The function print_vector shall print a vector which is
            specified similarly with three parameters.

Test:       1. by defining a global array consisting of 8 elements.
            2. by initilizing the entire array and printing it.
            3. by using the same global array for two consecutive vectors
            of length 4 which are each individually initialized and printed.
            4.by using the same global array for two interleaving vectors of
            length 4 which are likewise initialized and printed.*/

            
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
double vector[8];
int main(){
    double *x = vector;
    printf("initialize x as one vector\n");
    size_t max_size = sizeof(vector)/sizeof(vector[0]);
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

    
}
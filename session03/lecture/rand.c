#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef SEED
#define SEED 42
#endif

int main(void){
    printf("using seed = %u\n", SEED);
    srand(SEED);
    printf("rand() = %u\n", rand());
    printf("rand() = %u\n", rand());
    printf("rand() = %u\n", rand());

    printf("using seconds since 00:00:00 UTC on 1 January 1970 as seed ...\n");
    srand(time(0));
    printf("rand() = %u\n", rand());
    printf("rand() = %u\n", rand());    
    printf("rand() = %u\n", rand());
}
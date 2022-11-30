#include <stdio.h>

int main(){

    /*x is a pointer to x[0]
    incrementing x via x+2 increments the pointer
    result: x (dp) -> x[2]
    */
    double x[8] = {0};
    double* dp;
    dp = x + 2;
    printf("x = %p &dp = %p dp = %p\n",x, &dp, dp);
    *dp = 42;
    printf("x[2] = %lf\n",x[2]);
}
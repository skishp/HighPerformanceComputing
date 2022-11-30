#include <stdio.h>

int main(){
    /*subtracting pointers*/
    double x[8] = {0};
    double *dp1, *dp2;
    dp1 = x + 2;
    dp2 = x + 5;
    printf("dp1 - dp2 = %td\n", dp1-dp2);
    printf("dp2 - dp1 = %td \n", dp2 - dp1);
}
#include <stdio.h>

int main(){
    int i = 1;
    int j = 2;
    int *ip = 0;
    printf("addresses of i, j, and ip: %p, %p, %p\n", &i, &j, &ip);
    ip = &i;
    *ip = 42;
    printf("i = %d\n",i);
}
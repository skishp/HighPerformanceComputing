#include <stdio.h>

/*
Once foo returns the pointer to its local variable which ceases to exist, hence code in 
line 23 is undefined. Bar looks the same as foo, but the local variable gets another value, it is likely 
that both local variable get the same storage location
output = 77
*/

int* foo(){
    int val = 42;
    int* valp = &val;
    return valp;
}

int* bar(){
    int val = 77;
    int* valp = &val;
    return valp;
}

int main(){
    int* ip  = foo(); bar();
    printf("*ip = %d\n", *ip);
}
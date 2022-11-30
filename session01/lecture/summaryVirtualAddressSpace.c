#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

float x[] = {1.2, 3.4, 5.6}; //global data, initialized with non-zero values
double y[1024]; //global data, zero-initialized

int main(){
    int a[10];
    double* p = malloc(sizeof(double)*1024); //heap allocation
    printf("%18p main (text segment)\n",main);
    printf("%18p x (global_data, initialized with non-zero values)\n",x);    
    printf("%18p y (global_data, zero-initialized)\n",y);
    printf("%18p p (global on the heap\n", p);
    printf("%18p a (local variable on stack)\n", a);

    char cmd[32];
    snprintf(cmd, sizeof cmd, "pmap %d", (int) getpid());
    system(cmd);
}
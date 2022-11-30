#include <stdio.h>

int main(){
    int i = 42;
    printf("i occupies %zu bytes and is located at address %p.\n",
    sizeof(i),&i);
}
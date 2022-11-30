#include "printf.hpp" /*need for fmt::prinft*/

void f(int val){
    val = val +1;
}

int main(){
    int i = 1;
    f(i);
    fmt::printf("i=%d\n",i); /*i still 1*/
}

/*we have the same behaviour for objects
look at call2
*/
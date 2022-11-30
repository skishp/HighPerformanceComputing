#include <stdalign.h>
#include <stdio.h>

struct a {
    double x;
    int i;
};

int main(){
    /*printing size of int and alignment of int*/
    printf("int %2zu %2zu \n", sizeof(int),alignof(int));

    /*printing size of double and alignment of doulbe*/
    printf("double %2zu %2zu \n", sizeof(double),alignof(double));

    /*printing size of double[10] (otuput= 10*sizeof(double))
     and align of double[10](output = alignof(double))*/
    printf("double [10] %2zu %2zu \n", sizeof(double[10]),alignof(double[10]));

    /*printing size of struct a and alignof struct a
    note:       that size of struct a is sizeof(int)+sizeof(double)=12,
                but gets rounded to next multiple of alignmet of 8
    output:     sizeof(struct a) = 16 alignof(struct a) = 8 since there is doublei in struct a
    */
    printf("struct a %2zu %2zu\n", sizeof(struct a), alignof(struct a));
    

}
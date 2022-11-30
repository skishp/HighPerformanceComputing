## Exercise 01
Provide in `gematrix.c` implementations for the functions declared in `gmeatrix.h`
1. implement the allocation of memory for a Matrix
2. implement the function to free the memory used/declared. 

## Solution 01 
The implementation of ex01 can be found in `gematrix.c`. This functions are simple.
1. One have to check if the allocation was out of memory. 
2. We get a pointer to a `struct GeMatrix A` . We use `free(A->data)` to release the used memory. 

## Exercise 02
Provide in `geutils.c` implementations for the functions declared in `geutils.h`. 
1. Initilize the matrix with values from 1 to the dimension of the Matrix. 
2. Print the Matirx 

## Solution 02
The solution for this exercise can be found in `geutils.c`. 
1. One increments the pointer of the Matrix data 
```
A[i*incRow + j*incCol] = i*n + j+1;
```
We even don`t have to care about if the matrix is stored as a Col-Major oder Row-Major. We increment my a multiple of each stride and we're fine. 
2. The same incrementation of the pointer but only in a printf command
```
printf(" %4.1lf",A[i*incRow + j*incCol]);
```

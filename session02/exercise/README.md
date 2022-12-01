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
The output will be given in exercise 03. There we will be writing a test setup. 

## Exercise 03
Modify your test program to achieve the following:
* In `main`, initialize 7x8 `row major` matrix A. 
* Print matrix A. 
* Print the transposed matrix, i.e. A^T 
* Print the content of the allocated memory block as row vector of length m*n.
* Print the second row of the matrix. 
* Print the third column of the matrix.
* Print a submatrix
* Print the submatrix with reversed entries. 
Once you are done: Change the format from rowmajor to colmajor. The output should not change. 

## Solution 03
The coding solution can be found in `gematrix_3.c`. We use the print function of exercise 02. The special part in this exercise is, that we don't have to rewrite anything. We simply use the print function we wrote, by simply adjusting the input parameters of the print frunction we achieve all the tasks. 
Remind: the default input parameters are 
```
geprint(A.numRows, A.numCols, A.data, A.incRow, A.incCols);
```
by simply switching the rows and column input parameters we already achieve the transpostion of a matrix 
```
geprint(A.numCols,A.numRows,A.data,A.incCols,A.incRow);
```
For the other tasks we have to think about the incremetation of the pointers. For example if we want to print a Matrix as a vector then obviously we have to have the strides of incRow and incCol defined as 1. The amount of rows is now 1 and columns is m*n. This implementation can be seen in 
```
geprint(1, A.numCols*A.numRows, A.data, 1,1);
```
The rest of the tasks is done in similar fashion. We only have to becareful where we start with our pointer and consider the right strides. 

The output of those 3 tasks is given in output.png

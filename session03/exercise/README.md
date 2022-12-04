## Exercise 01
Implement the infinity norm of two matrices in `geutils.h` from session 02. For testing the norm write a program that does the following
* Allocate a 7x7 matrix A that get initialized with `geinit`
* Compute ||A - A|| and print its value (should be 0)
* Compute ||A - A^T|| and print its value (should be 126)
*
## Solution 01 
The implementation of the first task is given in `geutils.c`. First we remind us what the matrix infinity norm is. Its basically the maximum of the absolute value of the rows. Here the absolute value of a row stands for: summation of the absolute row entries. 
Since we reminded ourselves of the definition the exercise becomes very simple. All we have to do is to take the sum of the absolute value of the row entries and check if this value exceeds our previous maximum. The summation is done via two for loops. 
```
counter_current += abs(A[i*incRow + j*incCol] - B[i*incRowB + j*incColB]);
```
The check is done via 
```
if(counter_current>counter){
            counter = counter_current;
        }
```
The `counter_current` has to reset to 0 before we start the second loop. 
The output of this exercise can be viewed in exercise01.png. The testing is implemented in `test_gematrix.c`.

## Provided test bench
In this session we first were provided with the `test_bench.c` file. What this file does is measuring the time that our `geinit` function of session 02 in `geutils.c` takes to initialize a matrix in row major and then column major. 

The output of `test_bench.c` was stored and can be viewed in `initmatrix.data`. If you take a look at the table in `initmatrix.data` you might notice that the initialization in col-major takes longer than initialization in row-major. 

## Exercise 02
The upcoming exercises and sessions will be about `BLAS` (Basic Linear Algebra Subprograms). BLAS Level 1 functions operate on vectors. Therefore we we start with the exercises: 
* Write a function `dscal`that scales a vector x with alpha so that we have
```
x <- alpha * x
```

* Write a function `dswap` that swaps (i.e. interchanges) the elements of two vectors. 
* Write the so called `axpy` (alpha x plus y) that computes 
```
y <- alpha x + y
``` 
* Write a function `iamax` that returns the smallest index j such that 
``` 
|x_j| = max 0<=k<N |x_k|
```

## Solution 02 
The Solution is implemented in `Blas1.c`. The functions are relatively simple so that I will not comment on them. The output can be found in `exercise02.c`.
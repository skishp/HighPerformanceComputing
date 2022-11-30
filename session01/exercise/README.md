# Exercise 1
1. A function `init_vector` shall initialize a vector. The vector specified by a pointer to its first eleent, the number of elements, and the stride between two consecutive elements of the vector. The first element of the vector is to be initialized to 1, the second to 2 etc. 
2. The fucntion `print_vector` shall print a vector which is specified similarly with three parameters.

Test this 
* by defining a global array consisting of 8 Elements
* by initializing the entire array and printing it
* by using the same global array for two consecutive vectorss of length 4 whih are eahc individually initilized and printed, and
* by using the same global array for wto interleaving vectors of length 4 which are likewise initialized and printed. 

# Solution 01
The Coding solution can be found in `FirstStepsWithC.c`. The Output can be found in `Exercise01.png`.

# Exercise 02
Rewrite your solution for the exercise 01 to allow dynamic array length is is read from standard input. 

# Soltuion 02 
The code for the solution is found in `DynamicAllocationOfArrays`. User input is given via `scanf`. 
The main difference for the allocation of the array, that we use malloc
```
double *vector = malloc(sizeof(double)*max_size);
```
instead of 
```
double vector[8];
```
The output is the same as in Exercise01. However the interesting part it if use `valgrind` in the execution. This allows us to check if the allocated memory is freed or not and if there is memory leakage or not. An Example of this can be seen in `Exercise02.png`. 

# Exercise 03
It is interesting to see how the performance scales using variable vector lengths for powers of two in the range from 8192 to 67108864. To messure the performance for each of the lengths independently form eah other, you should for each legth
* allocate two big vectors twice as large as the length using `malloc` with pointers `vector1` and `vector2` pointing to it
* using the array behind `vector1`to store two vectors of the given length consecutively, 
* using the array behind `vecotr2`to store two interleaving vectors of the given length,
* releasing the arrays behind `vector1`and `vector2`using `free`. 

# Solution 03.
The code for the Solution can be found in `PerformanceInDepencdenceOfAccesPatterns.c`. The output contains the time comparision of the allcotion of the arrays and can be found in `Exercise03.png`. 
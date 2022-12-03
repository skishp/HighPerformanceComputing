## Exercise 01
In our previous implementation of the matrix class we allocated memory for our matrix via 
```
new double[m*n]
```
However we may want use other tpyes than double. This can be achieved by using Templates. 
Rewrite the matrix class so that it uses template and can use different types. 

## Solution 01 
The implementation can be found in `matrix_class8.cpp`. The key things to note here is that we use 
```
T* data;
```
in our matrix structure, where 
```
template<typename T>
```
is put infront of the structure. The rest of the matrix structure especially the functions are stayed the same. 
Now we can define matrixes of the specified type double via
```
Matrix<double> A(7, 8, StorageOrder::ColMajor);
```
or as float via
```
Matrix<float> B(3, 3, StorageOrder::RowMajor);
```
Note: the type is specified in `Matrix<type>`. Furthermore since we use our `printf.hpp` and print our matrix via 
```
fmt::printf()
```
We don't encounter any problems and errors at all. This is not the case if we use the `std::prinft()` function. But our `fmt::printf()` is far from perfect. If we want to implement a complex matrix, by relizing the complex number in a structure with real part and imaginary part
``` 
double re;
double im; 
``` 
the initialization of the matrix
```
Matrix<Complex> A(3, 3, StorageOrder::ColMajor);
```
will lead to an error. 

The output can be seen in `exercise01.png`.

## Exercise 02
The `init` and `print` function was realized within the matrix class. In this exercise we want to move the `init` and the `print` function out of the matrix class and turn it into a template function. This exercise is justified by the facts, that we want the code and classes to be
* minimalistic 
* sufficiently extensible at the same time such that we do not restrict possible applications of a class. 

## Solution 02
The implementation of this exercise is found in `matrix_class11.cpp`. The implementation is not hard and the output will still be the same matrix, so we refuse to give the output and further detailed explanation. 

## Exercise 03
In the current state, every matrix object had its own storage. We have, however, in our mathematical notation submatrices or block matrices which are part of larger matrix. It would be helpful to support such matrices without the need to duplicate allocated storage. Such a submatrix would not be responsible for 
* allocating storage
* releasing storage
It only provides a view to a larger matrix. This approach is known as `MVC` pattern, where MCV is an acronym for model,viewer and controller. 

* What happens if an entirel different type is passed to `print_matrix` (for example 1) instead of a matrix variable?
* Is it possible to have a MatrixView object that referes to another MatrixView object? 
* Fix the `init_matrix` template function such that it works also for instances of MatrixView. 
* By default, C++ offers a copy constructor and an assignment operator for each class which actually copies all individual object variables from m to data. Is it advisable to accept the default implementations for the matrix class? Is it a problem for the MatrixView class?  If you want to inhibit a default implementation just add the declaration with a = delete construct at its end. The following example inhibits the copy constructor and assignment operator for Matrix:
``` 
Matrix(const Matrix& other) = delete;
Matrix& operator=(const Matrix& other) = delete;
```
Test if inhibited copy constructors and assignment operators cease to work. And test whether the default implementations of the copy constructor and assignment operator work as expected where they are not suppressed.

The copy constructor is used when an object is declared and initialized with another object of the same type. The assignment operator is used whenever the assignment operator is used after the construction of the target object. Example:
```
MatrixView<double> C = B; // copy constructor
fmt::printf("C =\n"); print_matrix(C);
MatrixView<double> D = B; // copy constructor
D = C; // assignment operator
```
Develop a template function create_view that accepts an arbitrary matrix (be it Matrix or MatrixView) and delivers a submatrix as MatrixView. The parameters shall specify the index of the first element and the number of rows and columns. Example:
```
MatrixView<double> D(create_view(A, 1, 4, 3, 2));
fmt::printf("D =\n"); print_matrix(D);
```
However, if you want to write down the template function declaration for create_view you will run into a problem when you have to name the element type of the matrix while you have just the matrix type as parameter. There are different approaches for this problem in C++. The classical approach is to add a helpful type declaration within struct Matrix and struct MatrixView:
```
template<typename T>
struct /* Matrix or MatrixView */ {
   /* ... */
   typedef T Element;
};
```
Alternatively, a using-declaration can be used:

```
template<typename T>
struct /* Matrix or MatrixView */ {
   /* ... */
   using Element = T;
};
```
When this has been done, you are free to use Matrix::Element whenever you have a template type parameter named Matrix, provided all matrix classes support this convention. There is just another problem. As the C++ grammar has ambiguities which are only resolved by knowing whether a name specifies a type or something else, we need to help the C++ compiler where this cannot be deduced automatically by the compiler. In case of templates, the compiler cannot do this as the type parameter remains unknown before instantiation. This problem is solved by adding the keyword typename in front of a type where the compiler cannot resolve the ambiguity otherwise: 
```
typename Matrix::Element.
```
In addition, it might be helpful to add an assertion using assert that makes sure that the ranges of the submatrix are restricted to the ranges of the matrix it is derived from.

## Soltuion 03
1. In the first problem, if we pass 1, then the template function is instantiated with the template type parameter T set to int. Which means that our Matrix is now of type int. Expressions like `A.m` or `A(i,j)` won't work anymore. 
2. It is possible to have MatrixView object which is constructed from another MatrixView object as the constructor just expects dimensions, a pointer to the data, and the increments. 
Note: Here we have to becareful that the MatrixViews object do not outlive the associated storage which is maintained by the original Matrix object. 

The implementation for the other task is found in matrix_class13.cpp The output is given in exercise03.png


## Exercise 04
The `GMP` library (GMP is an acronym of GNU multiple precision library) provides numerical types with arbitrar precisions. The library provides, among other types, a class named `mpq_class` for rational numbers where the numerator and denominator are maintained as a seperated integer values of arbitrary precision. 
* Adapt `print_value` such that rational numbers are supported as well. 
* Add a template function `scale_matrix` that multiplies all elements of a matrix with given value. Use this function wen you test your programs with rational numbers.
* Test wether a `fmt::printf` based variant would work for rational numbers out of the box. 


## Solution 04
The solution of the first to tasks is implemented in `matrix_class17.cpp`. The output is given in `exercise04_01.png`. How ever for the 3. task there will be a error which can be seen in `exercise04_2.png`. The code for the implementation is in `matrix_class17.cpp`. It failed since there was no output operator provided for `mpq_class` operators. 
A provided solution to this problem can be seen in matrix_class18. The output of the fixed error is documented in `exercise04_2.fixed.png`

The operator 
```
std::ostream& operator<<(std::ostream& out, const mpq_class& value) {
   return out << value.get_str().c_str();
}
```
fixed the issue. 
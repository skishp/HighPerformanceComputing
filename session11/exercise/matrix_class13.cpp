#include <cassert> /* needed for assert */
#include <cstddef> /* needed for std::size_t and std::ptrdiff_t */
#include "printf.hpp" /* needed for fmt::printf */

enum class StorageOrder {ColMajor, RowMajor};

template<typename T>
struct Matrix {
   const std::size_t m; /* number of rows */
   const std::size_t n; /* number of columns */
   const std::ptrdiff_t incRow;
   const std::ptrdiff_t incCol;
   T* data;
   using Element = T;

   Matrix(std::size_t m, std::size_t n, StorageOrder order) :
         m(m), n(n),
         incRow(order == StorageOrder::ColMajor? 1: n),
         incCol(order == StorageOrder::RowMajor? 1: m),
         data(new T[m*n]) {
   }
   Matrix(const Matrix& other) = delete;

   ~Matrix() {
      delete[] data;
   }

   Matrix& operator=(const Matrix& other) = delete;

   const T& operator()(std::size_t i, std::size_t j) const {
      assert(i < m && j < n);
      return data[i*incRow + j*incCol];
   }
   
   T& operator()(std::size_t i, std::size_t j) {
      assert(i < m && j < n);
      return data[i*incRow + j*incCol];
   }
};

template<typename T>
struct MatrixView {
   const std::size_t m; /* number of rows */
   const std::size_t n; /* number of columns */
   const std::ptrdiff_t incRow;
   const std::ptrdiff_t incCol;
   T* data;
   using Element = T;

   MatrixView(std::size_t m, std::size_t n,
            T* data,
            std::ptrdiff_t incRow, std::ptrdiff_t incCol) :
         m(m), n(n), 
         incRow(incRow), incCol(incCol),
         data(data) {
   }

   const T& operator()(std::size_t i, std::size_t j) const {
      assert(i < m && j < n);
      return data[i*incRow + j*incCol];
   }
   
   T& operator()(std::size_t i, std::size_t j) {
      assert(i < m && j < n);
      return data[i*incRow + j*incCol];
   }
};

template<typename Matrix>
void init_matrix(Matrix& A) {
   for (std::size_t i = 0; i < A.m; ++i) {
      for (std::size_t j = 0; j < A.n; ++j) {
         A(i, j) = j * A.m + i + 1;
      }
   }
}

template<typename Matrix>
void print_matrix(const Matrix& A) {
   for (std::size_t i = 0; i < A.m; ++i) {
      fmt::printf("  ");
      for (std::size_t j = 0; j < A.n; ++j) {
         fmt::printf(" %4.1lf", A(i, j));
      }
      fmt::printf("\n");
   }
}

template<typename Matrix>
MatrixView<typename Matrix::Element> create_view(Matrix& A,
      std::size_t i, std::size_t j,
      std::size_t m, std::size_t n) {
   assert(i + m <= A.m && j + n <= A.n);
   return MatrixView<typename Matrix::Element>(m, n, &A(i, j),
      A.incRow, A.incCol);
}

int main() {
   Matrix<double> A(7, 8, StorageOrder::ColMajor);
   MatrixView<double> B(3, 3, &A(2, 2), A.incRow, A.incCol);

   init_matrix(A);
   B(1, 1) = 0;
   fmt::printf("A =\n"); print_matrix(A);
   fmt::printf("B =\n"); print_matrix(B);

   MatrixView<double> C = B;
   fmt::printf("C =\n"); print_matrix(C);

   MatrixView<double> D(create_view(A, 1, 4, 3, 2));
   fmt::printf("D =\n"); print_matrix(D);
}
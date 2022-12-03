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

   Matrix(std::size_t m, std::size_t n, StorageOrder order) :
         m(m), n(n),
         incRow(order == StorageOrder::ColMajor? 1: n),
         incCol(order == StorageOrder::RowMajor? 1: m),
         data(new T[m*n]) {
   }

   ~Matrix() {
      delete[] data;
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

template<typename T>
void init_matrix(Matrix<T>& A) {
   for (std::size_t i = 0; i < A.m; ++i) {
      for (std::size_t j = 0; j < A.n; ++j) {
         A(i, j) = j * A.m + i + 1;
      }
   }
}

template<typename T>
void print_matrix(const Matrix<T>& A) {
   for (std::size_t i = 0; i < A.m; ++i) {
      fmt::printf("  ");
      for (std::size_t j = 0; j < A.n; ++j) {
         fmt::printf(" %4.1lf", A(i, j));
      }
      fmt::printf("\n");
   }
}

int main() {
   Matrix<double> A(7, 8, StorageOrder::ColMajor);
   init_matrix(A); fmt::printf("A =\n"); print_matrix(A);
}
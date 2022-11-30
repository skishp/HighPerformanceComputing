#include <cassert> /* needed for assert */
#include <cstddef> /* needed for std::size_t and std::ptrdiff_t */
#include "printf.hpp" /* needed for fmt::printf */

enum class StorageOrder {ColMajor, RowMajor};

struct Matrix {
   const std::size_t m; /* number of rows */
   const std::size_t n; /* number of columns */
   const std::ptrdiff_t incRow;
   const std::ptrdiff_t incCol;
   double* data;

   Matrix(std::size_t m, std::size_t n, StorageOrder order) :
         m(m), n(n),
         incRow(order == StorageOrder::ColMajor? 1: n),
         incCol(order == StorageOrder::RowMajor? 1: m),
         data(new double[m*n]) {
   }

   const double& operator()(std::size_t i, std::size_t j) const {
      assert(i < m && j < n);
      return data[i*incRow + j*incCol];
   }
   
   double& operator()(std::size_t i, std::size_t j) {
      assert(i < m && j < n);
      return data[i*incRow + j*incCol];
   }

   void init() {
      for (std::size_t i = 0; i < m; ++i) {
         for (std::size_t j = 0; j < n; ++j) {
            data[i*incRow + j*incCol] = j * m + i + 1;
         }
      }
   }

   void print() {
      for (std::size_t i = 0; i < m; ++i) {
         fmt::printf("  ");
         for (std::size_t j = 0; j < n; ++j) {
            fmt::printf(" %4.1lf", data[i*incRow + j*incCol]);
         }
         fmt::printf("\n");
      }
   }
};

void copy_matrix(const Matrix& A, Matrix& B) {
   /* copy A to B */
   assert(A.m == B.m && A.n == B.n);
   for (std::size_t i = 0; i < A.m; ++i) {
      for (std::size_t j = 0; j < A.n; ++j) {
         B(i, j) = A(i, j);
      }
   }
}

int main() {
   Matrix A(7, 8, StorageOrder::ColMajor);
   A.init();
   fmt::printf("A =\n"); A.print();
   Matrix B(7, 8, StorageOrder::RowMajor);
   copy_matrix(A, B);
   fmt::printf("B =\n"); B.print();
   delete[] A.data;
   delete[] B.data;
}
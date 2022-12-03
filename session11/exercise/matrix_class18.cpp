#include <cassert> /* needed for assert */
#include <cstddef> /* needed for std::size_t and std::ptrdiff_t */
#include <gmpxx.h> /* GNU Multiple Precision Library, needed for mpq_class */
#include "printf.hpp" /* needed for fmt::printf */

enum class StorageOrder {ColMajor, RowMajor};

template<typename T>
struct Matrix {
   const std::size_t m; /* number of rows */
   const std::size_t n; /* number of columns */
   const std::size_t incRow;
   const std::size_t incCol;
   T* data;
   using Element = T;

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
struct MatrixView {
   const std::size_t m; /* number of rows */
   const std::size_t n; /* number of columns */
   const std::size_t incRow;
   const std::size_t incCol;
   T* data;
   using Element = T;

   MatrixView(std::size_t m, std::size_t n,
            T* data,
            std::size_t incRow, std::size_t incCol) :
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
         fmt::printf(" %9.1f", A(i, j));
      }
      fmt::printf("\n");
   }
}

template<typename Matrix, typename T>
void scale_matrix(Matrix& A, const T& alpha) {
   for (std::size_t i = 0; i < A.m; ++i) {
      for (std::size_t j = 0; j < A.n; ++j) {
         A(i, j) *= alpha;
      }
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

std::ostream& operator<<(std::ostream& out, const mpq_class& value) {
   return out << value.get_str().c_str();
}

int main() {
   Matrix<mpq_class> A(7, 8, StorageOrder::ColMajor);
   init_matrix(A);
   scale_matrix(A, mpq_class(1, 3));
   fmt::printf("A =\n"); print_matrix(A);
}
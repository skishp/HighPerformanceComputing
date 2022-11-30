#include <cstddef> /* needed for std::size_t and std::ptrdiff_t */
#include <cassert> /* needed for assert */
#include "printf.hpp" /* needed for fmt::printf */

enum class StorageOrder {ColMajor, RowMajor};

struct Matrix {
   const char* name; /* for debugging purposes */
   const std::size_t m; /* number of rows */
   const std::size_t n; /* number of columns */
   const std::ptrdiff_t incRow;
   const std::ptrdiff_t incCol;
   double* data;

   Matrix(const char* name,
         std::size_t m, std::size_t n, StorageOrder order) :
         name(name),
         m(m), n(n),
         incRow(order == StorageOrder::ColMajor? 1: n),
         incCol(order == StorageOrder::RowMajor? 1: m),
         data(new double[m*n]) {
      fmt::printf("constructing %s\n", name);
   }

   ~Matrix() {
      fmt::printf("destructing %s\n", name);
      delete[] data;
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

Matrix A("A (global)", 7, 8, StorageOrder::ColMajor);

int main() {
   {
      Matrix B("B (local)", 7, 8, StorageOrder::ColMajor);
   }
   Matrix("temporary", 7, 8, StorageOrder::ColMajor);
   Matrix* m = new Matrix("on heap", 7, 8, StorageOrder::RowMajor);
   delete m;
}
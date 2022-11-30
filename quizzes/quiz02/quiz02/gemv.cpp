#include <cassert>
#include "gemv.hpp"
#include "matrix.hpp"
#include "vector.hpp"


// y \leftarrow \beta y + \alpha A x
void gemv(double alpha, const Matrix &A, const Vector &x,
          double beta, Vector &y)
{
   // FIXME
   assert(A.n == x.length && A.m == y.length);
   if (alpha == 0)
   {
      return;
   }
   if (beta != 1)
   {
      for (std::size_t i = 0; i < y.length; ++i)
      {
         y(i) = y(i)* beta;
      }
   }
   for (std::size_t i = 0; i < A.m; ++i)
   {
      for (std::size_t j = 0; j < A.n; ++j)
      {

         y(i) += alpha* A(i, j) * x(j);
      }
   }
}

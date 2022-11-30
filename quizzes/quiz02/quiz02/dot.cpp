#include <cassert>
#include <cstdlib>
#include "dot.hpp"
#include "vector.hpp"

double dot(const Vector &x, const Vector &y)
{
   // FIXME
   assert(x.length == y.length);
   double a;
   for (std::size_t i = 0; i < x.length; ++i)
   {
      a += x(i) * y(i);
   }
   return a;
}

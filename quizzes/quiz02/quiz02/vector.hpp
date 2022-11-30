#ifndef HPC_VECTOR_HPP
#define HPC_VECTOR_HPP

#include <cassert>
#include <cstdlib>

struct Vector {
   // FIXME
   const std::size_t length;
   double* data;
   Vector(std::size_t length):length(length),data(new double[length])
      /* FIXME */
   {
   }

   ~Vector() {
      // FIXME
      delete[] data;
   }

   const double& operator()(std::size_t i) const {
      // FIXME
      assert(i<length);
      return data[i];
   }

   double& operator()(std::size_t i) {
      // FIXME
      assert(i<length);
      return data[i];
   }

   void init() {
      // FIXME
      for(std::size_t i = 0; i<length; ++i){
         data[i] = i;
      }
   }
};

#endif

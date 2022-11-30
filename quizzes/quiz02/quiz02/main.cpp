#include <cstddef>
#include <iostream>

#include "vector.hpp"
#include "dot.hpp"
#include "matrix.hpp"
#include "gemv.hpp"

int main()
{
    struct Vector v(3);
    v.init();

    struct Vector w(3);
    w.init();
    
    struct Matrix M(3,3,StorageOrder::RowMajor);
    M.init();
    M.print();
    gemv(1,M,v,0,w);
    for(std::size_t i = 0; i<w.length;++i){
        std::cout <<w(i)<<std::endl;
    }

}
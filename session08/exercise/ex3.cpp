#include <cstddef>
#include "printf.hpp"

namespace tools
{

    /* TODO: Your code for class DoubleArray */

    /* TODO: Your code for class DoubleArray */
    struct DoubleArray
    {
        DoubleArray(std::size_t n) : ptr(new double[n])
        {
            fmt::printf("DoubleArray(): array allocated at %p\n", ptr);
        }
        ~DoubleArray()
        {
            fmt::printf("~DoubleArray(): delete [] %p\n", ptr);
            delete[] ptr;
        }
        double &operator[](std::size_t i) const
        {
            return ptr[i];
        }
        double *const ptr;
    };

} // namespace tools

int main()
{
    // Allocate a buffer with length 10 on heap
    tools::DoubleArray p(10);
    tools::DoubleArray q(10);

    q = p;

    fmt::printf("main(): Hope somehow all my trash gets removed\n");
}
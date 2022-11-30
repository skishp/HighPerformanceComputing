#include <cstdlib>
#include <cstddef>
#include "printf.hpp"

namespace tools
{

    struct DoubleArray
    {
        DoubleArray(const DoubleArray &) = delete;

        DoubleArray(std::size_t n)
            : ptr(new double[n])
        {
            if (!ptr)
            {
                std::abort();
            }
            fmt::printf("DoubleArray(): array allocated at %p\n", ptr);
        }

        ~DoubleArray()
        {
            fmt::printf("~DoubleArray(): delete [] %p\n", ptr);
            delete[] ptr;
        }

        operator double *() const
        {
            return ptr;
        }

        double *const ptr;
    };

} // namespace tools

void printArray(std::size_t n, const double *x)
{
    for (std::size_t i = 0; i < n; ++i)
    {
        fmt::printf("%10.3lf", x[i]);
    }
    fmt::printf("\n");
}

int main()
{
    // Allocate a buffer with length 10 on heap
    tools::DoubleArray p(10);

    for (std::size_t i = 0; i < 10; ++i)
    {
        p[i] = i;
    }

    // Getting a raw pointer because p can be converted to `double *'
    printArray(10, p);
    // Getting a raw pointer by taking the address of an array element
    printArray(10, &p[0]);

    fmt::printf("main(): Hope somehow all my trash gets removed\n");
}
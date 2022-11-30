#include <cstddef>
#include <cstdlib>
#include "printf.hpp"

namespace tools {

void
initMatrix(std::size_t m, std::size_t n,
           double *A, std::ptrdiff_t incRowA, std::ptrdiff_t incColA)
{
    for (std::size_t j = 0; j < n; ++j) {
        for (std::size_t i = 0; i < m; ++i) {
            A[i * incRowA + j * incColA] = i * n + j + 1;
        }
    }
}

void
printMatrix(std::size_t m, std::size_t n,
            const double *A, std::ptrdiff_t incRowA, std::ptrdiff_t incColA)
{
    for (std::size_t i = 0; i < m; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            fmt::printf("%6.2lf ", A[i * incRowA + j * incColA]);
        }
        fmt::printf("\n");
    }
    fmt::printf("\n");
}

struct DoubleArray
{
    DoubleArray(std::size_t n)
      : ptr(new double[n])
    {
        if (!ptr) {
            std::abort();
        }
    }

    ~DoubleArray()
    {
        delete[] ptr;
    }

    operator double *() const
    {
        return ptr;
    }

    double *const ptr;
};

} // namespace tools
//------------------------------------------------------------------------------

namespace ulmblas {

void
pack_A(std::size_t M, std::size_t K,
       const double *A, std::ptrdiff_t incRowA, std::ptrdiff_t incColA,
       std::size_t M_R,
       double *p)
{
    std::size_t m_p = (M + M_R - 1) / M_R;

    if (incRowA < incColA) {
        for (std::size_t J = 0; J < K; ++J) {
            for (std::size_t I = 0; I < M_R * m_p; ++I) {
                std::size_t mu = M_R * K * (I / M_R) + J * M_R + (I % M_R);

                p[mu] = (I < M) ? A[I * incRowA + J * incColA] : 0;
            }
        }
    } else {
        for (std::size_t I = 0; I < M_R * m_p; ++I) {
            for (std::size_t J = 0; J < K; ++J) {
                std::size_t mu = M_R * K * (I / M_R) + J * M_R + (I % M_R);

                p[mu] = (I < M) ? A[I * incRowA + J * incColA] : 0;
            }
        }
    }
}

} // namespace ulmblas

//------------------------------------------------------------------------------

#ifndef DIM_M
#define DIM_M 9
#endif

#ifndef DIM_K
#define DIM_K 11
#endif

#ifndef COLMAJOR_A
#define COLMAJOR_A 1
#endif

std::size_t M_C = 6;
std::size_t K_C = 4;
std::size_t M_R = 2;

//------------------------------------------------------------------------------

int
main(void)
{
    // For the moment we will not use the matrix class from session 7
    // 1) Allocate a m x k matrix
    std::size_t m = DIM_M;
    std::size_t k = DIM_K;
    tools::DoubleArray A(m * k);
    std::ptrdiff_t incRowA = (COLMAJOR_A) ? 1 : k;
    std::ptrdiff_t incColA = (COLMAJOR_A) ? m : 1;

    // 2) Initialize matrix A
    tools::initMatrix(m, k, A, incRowA, incColA);

    // 3) Print dimensions of A and content of A
    fmt::printf("m = %zu, k = %zu\n", m, k);
    fmt::printf("A = \n");
    tools::printMatrix(m, k, A, incRowA, incColA);

    fmt::printf("M_C = %zu, K_C = %zu, M_R = %zu\n", M_C, K_C, M_R);

    // 4) Allocate a buffer p of size M_C * K_C
    tools::DoubleArray p(M_C * K_C);

    std::size_t m_b = (m + M_C - 1) / M_C;
    std::size_t k_b = (k + K_C - 1) / K_C;

    fmt::printf("A is partitioned into a %zu x %zu block matrix\n", m_b, k_b);

    std::size_t M_ = m % M_C;
    std::size_t K_ = k % K_C;

    for (std::size_t i = 0; i < m_b; ++i) {
        std::size_t M = (i != m_b - 1 || M_ == 0) ? M_C : M_;
        for (std::size_t j = 0; j < k_b; ++j) {
            std::size_t K = (j != k_b - 1 || K_ == 0) ? K_C : K_;
            fmt::printf("A_{%zu,%zu} is a %zu x %zu matrix\n", i, j, M, K);

            // 5) Print the content of the matrix block A_{i,j}
            fmt::printf("A_{%zu,%zu} = \n", i, j);
            tools::printMatrix(M, K, &A[i * M_C * incRowA + j * K_C * incColA],
                               incRowA, incColA);

            // 6) Pack block A_{i,j} in buffer p
            ulmblas::pack_A(M, K, &A[i * M_C * incRowA + j * K_C * incColA],
                            incRowA, incColA, M_R, p);

            // 7) Print content of buffer p
            tools::printMatrix(1, M_C * K_C, p, 0, 1);
        }
    }
}
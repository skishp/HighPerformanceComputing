#include <cstddef>
#include "printf.hpp"

#ifndef DIM_M
#define DIM_M 10
#endif

#ifndef DIM_K
#define DIM_K 11
#endif

int main()
{
    std::size_t M_C = 6;
    std::size_t K_C = 4;
    std::size_t M_R = 2;

    std::size_t m = DIM_M;
    std::size_t k = DIM_K;

    fmt::printf("M_C = %zu, K_C = %zu, M_R = %zu\n", M_C, K_C, M_R);
    fmt::printf("m = %zu, k = %zu\n", m, k);

    std::size_t m_b = (m + M_C - 1) / M_C;
    std::size_t k_b = (k + K_C - 1) / K_C;

    fmt::printf("A is partitioned into a %zu x %zu block matrix\n", m_b, k_b);

    std::size_t M_ = m % M_C;
    std::size_t K_ = k % K_C;

    for (std::size_t i = 0; i < m_b; ++i)
    {
        std::size_t M = (i != m_b - 1 || M_ == 0) ? M_C
                                                  : M_;
        for (std::size_t j = 0; j < k_b; ++j)
        {
            std::size_t K = (j != k_b - 1 || K_ == 0) ? K_C
                                                      : K_;
            fmt::printf("A_{%zu,%zu} is a %zu x %zu matrix\n", i, j, M, K);

            std::size_t m_p = (M + M_R - 1) / M_R;

            fmt::printf("A_{%zu,%zu} has %zu horizontal panels\n", i, j, m_p);
        }
    }
}
#include <cassert> // for assert()
#include <cstddef> // for std::size_t, std::ptrdiff_t
#include <cstdlib> // for abort()

//------------------------------------------------------------------------------

#ifndef DUGEMM_MR_DEFAULT
#define DUGEMM_MR_DEFAULT 4
#endif

#ifndef DUGEMM_NR_DEFAULT
#define DUGEMM_NR_DEFAULT 64
#endif

#ifndef DGEMM_MC_DEFAULT
#define DGEMM_MC_DEFAULT 256
#endif

#ifndef DGEMM_NC_DEFAULT
#define DGEMM_NC_DEFAULT 2048
#endif

#ifndef DGEMM_KC_DEFAULT
#define DGEMM_KC_DEFAULT 256
#endif

//------------------------------------------------------------------------------
// Tool for handling buffers from session 8
//------------------------------------------------------------------------------

namespace tools
{

    struct DoubleArray
    {
        // TODO
        DoubleArray(const DoubleArray &) = delete;
        DoubleArray(std::size_t n) : ptr(new double[n])
        {
            if (!ptr)
            {
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
// BLAS Level 1 functions (for matrices)
//------------------------------------------------------------------------------

namespace ulmblas
{

    void
    gescal(std::size_t m, std::size_t n, double alpha,
           double *A, std::ptrdiff_t incRowA, std::ptrdiff_t incColA)
    {
        // TODO
        if (m == 0 || n == 0 || alpha == 1)
        {
            return;
        }
        // A is row major: scale A^T
        if (incRowA > incColA)
        {
            gescal(n, m, alpha, A, incColA, incRowA);
            return;
        }
        // A is col major:
        if (alpha != 0)
        {
            for (std::size_t j = 0; j < n; ++j)
            {
                for (std::size_t i = 0; i < m; ++i)
                {
                    A[i * incRowA + j * incColA] *= alpha;
                }
            }
        }
        else
        {
            for (std::size_t j = 0; j < n; ++j)
            {
                for (std::size_t i = 0; i < m; ++i)
                {
                    A[i * incRowA + j * incColA] = 0;
                }
            }
        }
    }

    void
    geaxpy(std::size_t m, std::size_t n, double alpha,
           const double *A, std::ptrdiff_t incRowA, std::ptrdiff_t incColA,
           double *B, std::ptrdiff_t incRowB, std::ptrdiff_t incColB)
    {
        // TODO
        if (m == 0 || n == 0 || alpha == 0)
        {
            return;
        }
        // if B is row major:   B^T <- alpha*A^T + B^T
        if (incRowB > incColB)
        {
            geaxpy(n, m, alpha, A, incColA, incRowA, B, incColB, incRowB);
            return;
        }
        // B is col major:
        for (std::size_t j = 0; j < n; ++j)
        {
            for (std::size_t i = 0; i < m; ++i)
            {
                B[i * incRowB + j * incColB] += alpha * A[i * incRowA + j * incColA];
            }
        }
    }

} // namespace ulmblas

//------------------------------------------------------------------------------
// GEMM micro kernel
//------------------------------------------------------------------------------

namespace ulmblas
{

    namespace dugemm_parameter
    {
        std::size_t MR = DUGEMM_MR_DEFAULT;
        std::size_t NR = DUGEMM_NR_DEFAULT;
    } // namespace dugemm_parameter

    void
    ugemm_ref(std::size_t k, double alpha,
              const double *A, const double *B,
              double beta,
              double *C, std::ptrdiff_t incRowC, std::ptrdiff_t incColC)
    {
        using namespace dugemm_parameter;

        // TODO
        double AB[MR * NR];

        for (std::size_t i = 0; i < MR * NR; ++i)
        {
            AB[i] = 0;
        }
        for (std::size_t l = 0; l < k; ++l)
        {
            for (std::size_t i = 0; i < MR; ++i)
            {
                for (std::size_t j = 0; j < NR; ++j)
                {
                    AB[i * NR + j] += A[i] * B[j];
                }
            }
            A += MR;
            B += NR;
        }
        // Yeah, this is unnecessary if (alpha==0). But ok ...
        for (std::size_t i = 0; i < MR * NR; ++i)
        {
            AB[i] *= alpha;
        }
        // This check for beta is really necessary
        if (beta != 0)
        {
            for (std::size_t j = 0; j < NR; ++j)
            {
                for (std::size_t i = 0; i < MR; ++i)
                {
                    C[i * incRowC + j * incColC] *= beta;
                    C[i * incRowC + j * incColC] += AB[i * NR + j];
                }
            }
        }
        else
        {
            for (std::size_t j = 0; j < NR; ++j)
            {
                for (std::size_t i = 0; i < MR; ++i)
                {
                    C[i * incRowC + j * incColC] = AB[i * NR + j];
                }
            }
        }
    }

} // namespace ulmblas

//------------------------------------------------------------------------------
// Packing matrix blocks for GEMM
//------------------------------------------------------------------------------

namespace ulmblas
{

    void
    pack_A(std::size_t M, std::size_t K,
           const double *A, std::ptrdiff_t incRowA, std::ptrdiff_t incColA,
           std::size_t M_R,
           double *p)
    {
        // TODO
        std::size_t m_p = (M + M_R - 1) / M_R;

        if (incRowA < incColA)
        {
            for (std::size_t J = 0; J < K; ++J)
            {
                for (std::size_t I = 0; I < M_R * m_p; ++I)
                {
                    std::size_t mu = M_R * K * (I / M_R) + J * M_R + (I % M_R);

                    p[mu] = (I < M) ? A[I * incRowA + J * incColA] : 0;
                }
            }
        }
        else
        {
            for (std::size_t I = 0; I < M_R * m_p; ++I)
            {
                for (std::size_t J = 0; J < K; ++J)
                {
                    std::size_t mu = M_R * K * (I / M_R) + J * M_R + (I % M_R);

                    p[mu] = (I < M) ? A[I * incRowA + J * incColA] : 0;
                }
            }
        }
    }

    void
    pack_B(std::size_t K, std::size_t N,
           const double *B, std::ptrdiff_t incRowB, std::ptrdiff_t incColB,
           std::size_t N_R,
           double *p)
    {
        // TODO
        pack_A(N, K, B, incColB, incRowB, N_R, p);
    }

} // namespace ulmblas

//------------------------------------------------------------------------------
// GEMM macro kernel
//------------------------------------------------------------------------------

namespace ulmblas
{

    void
    mgemm(std::size_t M, std::size_t N, std::size_t K,
          double alpha,
          const double *A, const double *B,
          double beta,
          double *C, std::ptrdiff_t incRowC, std::ptrdiff_t incColC)
    {
        using namespace dugemm_parameter;

        // TODO
        std::size_t mp = (M + MR - 1) / MR;
        std::size_t np = (N + NR - 1) / NR;

        std::size_t mr_ = M % MR;
        std::size_t nr_ = N % NR;

        double C_[MR * NR];

        for (std::size_t i = 0; i < mp; ++i)
        {
            std::size_t mr = (i < mp - 1 || mr_ == 0) ? MR
                                                      : mr_;
            for (std::size_t j = 0; j < np; ++j)
            {
                std::size_t nr = (j < np - 1 || nr_ == 0) ? NR
                                                          : nr_;

                if (mr == MR && nr == NR)
                {
                    ugemm_ref(K, alpha,
                              &A[i * MR * K], &B[j * K * NR],
                              beta,
                              &C[i * MR * incRowC + j * NR * incColC], incRowC, incColC);
                }
                else
                {
                    ugemm_ref(K, alpha,
                              &A[i * MR * K], &B[j * K * NR],
                              0,
                              C_, 1, MR);
                    gescal(mr, nr, beta,
                           &C[i * MR * incRowC + j * NR * incColC], incRowC, incColC);
                    geaxpy(mr, nr, 1,
                           C_, 1, MR,
                           &C[i * MR * incRowC + j * NR * incColC], incRowC, incColC);
                }
            }
        }
    }

} // namespace ulmblas

//------------------------------------------------------------------------------
// GEMM frame algorithm
//------------------------------------------------------------------------------

namespace ulmblas
{

    namespace dgemm_parameter
    {
        std::size_t MC = DGEMM_MC_DEFAULT;
        std::size_t NC = DGEMM_NC_DEFAULT;
        std::size_t KC = DGEMM_KC_DEFAULT;
    } // namespace dgemm_parameter

    void
    gemm(std::size_t m, std::size_t n, std::size_t k,
         double alpha,
         const double *A, std::ptrdiff_t incRowA, std::ptrdiff_t incColA,
         const double *B, std::ptrdiff_t incRowB, std::ptrdiff_t incColB,
         double beta,
         double *C, std::ptrdiff_t incRowC, std::ptrdiff_t incColC)
    {
        using namespace dugemm_parameter;
        using namespace dgemm_parameter;

        assert(MC % MR == 0);
        assert(NC % NR == 0);

        // TODO
        if (alpha == 0 || k == 0)
        {
            gescal(m, k, beta, C, incRowC, incColC);
            return;
        }
        std::size_t mb = m / MC;
        std::size_t nb = n / NC;
        std::size_t kb = k / KC;

        std::size_t nb_ = n % NC;
        std::size_t kb_ = k % KC;
        std::size_t mb_ = m % MC;
        

        for (std::size_t j = 0; j < nb; ++j)
        {
            std::size_t n_b = (j < nb - 1 || nb_ == 0) ? NC
                                                       : nb_;
            for (std::size_t l = 0; l < kb; ++l)
            {
                std::size_t k_b = (j < kb - 1 || kb_ == 0) ? KC
                                                           : kb_;
                tools::DoubleArray p_b(k_b * n_b);
                pack_B(k_b, n_b, B, incRowB, incColB, NR, p_b);

                for (std::size_t i = 0; i < mb; ++i)
                {
                    std::size_t m_b = (j < mb - 1 || mb_ == 0) ? MC
                                                               : mb_;
                    tools::DoubleArray p_a(m_b * n_b);
                    pack_A(m_b, k_b, A, incRowA, incColA, MR, p_a);
                    
                    mgemm(m_b, n_b, k_b, alpha, p_a, p_b, beta, C, incRowA, incColC);
                }
            }
        }
    }

} // namespace ulmblas

extern "C" {
void
ulm_dgemm_(const char *transA, const char *transB,
const int *m, const int *n, const int *k, const double *alpha,
const double *A, const int *ldA, const double *B, const int *ldB,
const double *beta, double *C, const int *ldC)
{
// Call your C++ implementation.
// Do *not* allocate any memory within this wrapper.
    if(*transA == 'n' || *transA == 'N'){
        if(*transB =='n' || *transB == 'N'){
            ulmblas::gemm(*m,*n,*k,*alpha,A,1,*ldA,B,1,*ldB,*beta,C,1,*ldC);
        }else{
            ulmblas::gemm(*m,*n,*k,*alpha,A,1,*ldA,B,*ldB,1,*beta,C,1,*ldC);
        }
    }else{
        if(*transB == 'n' || *transB == 'N'){
            ulmblas::gemm(*m,*n,*k,*alpha,A,*ldA,1,B,1,*ldB,*beta,C,1,*ldC);
        }else{
            ulmblas::gemm(*m,*n,*k,*alpha,A,*ldA,1,B,*ldB,1,*beta,C,1,*ldC);
        }
    }
}
} // extern "C
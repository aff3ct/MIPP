// --8<-- [start:includes]
#include <cstddef>
#include <cstdint>
#include <mipp.hpp>
// --8<-- [end:includes]

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        B[i] = (float)(i % 5) - 2.f;
    }
}

// §3.5: template deduction
static void auto_deduction()
{
    const float* ptr_a = A;
    const float* ptr_b = B;
    // --8<-- [start:auto_deduction]
    auto a = mipp::load<float>(ptr_a); // Deduced as mipp::rvd<float, 1, DEFAULT_ISA>
    auto b = mipp::load<float>(ptr_b);

    // Automatically deduces T=float, LMUL=1, and ISA_TYPE=DEFAULT_ISA:
    auto c = mipp::add(a, b);
    // --8<-- [end:auto_deduction]
    mipp::storeu(OUT, c);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(OUT[i] == A[i] + B[i]);
}

// §3.5: explicit template parameters
static void explicit_params()
{
    // --8<-- [start:explicit_params]
    auto zeroes = mipp::set0<double, 2>();       // mipp::rvd<double, 2>
    auto scalar_val = mipp::set1<int32_t>(42);   // mipp::rvd<int32_t, 1>
    // --8<-- [end:explicit_params]
    double z[DOC_BUF];
    int32_t s[DOC_BUF];
    mipp::storeu(z, zeroes);
    mipp::storeu(s, scalar_val);
    for (int i = 0; i < (int)mipp::N<double, 2>(); i++)
        DOC_CHECK(z[i] == 0.0);
    for (int i = 0; i < (int)mipp::N<int32_t>(); i++)
        DOC_CHECK(s[i] == 42);
}

// §3.6: masked operation
static void masked()
{
    auto a = mipp::load<float>(A);
    auto b = mipp::load<float>(B);
    auto m = mipp::cmplt(a, b);
    // --8<-- [start:masked]
    auto c = mipp::add<mipp::M, float>(m, a, b); // res[i] = m[i] ? a[i] + b[i] : a[i]
    // --8<-- [end:masked]
    mipp::storeu(OUT, c);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(OUT[i] == (A[i] < B[i] ? A[i] + B[i] : A[i]));
}

// §5: remainder handled with masked memory accesses
// --8<-- [start:masked_tail]
// y[i] = a * x[i] + y[i]
void saxpy(std::size_t n, float a, const float* x, float* y)
{
    constexpr std::size_t N = mipp::N<float>();
    const auto va = mipp::set1<float>(a);

    std::size_t i = 0;
    for (; i + N <= n; i += N) {
        auto vx = mipp::loadu<float>(x + i);
        auto vy = mipp::loadu<float>(y + i);
        mipp::storeu(y + i, mipp::fmadd(va, vx, vy));
    }

    if (i < n) { // fewer than N elements left
        int32_t active[N];
        for (std::size_t j = 0; j < N; j++)
            active[j] = (i + j < n);
        auto m  = mipp::set_k<float>(active); // lane j active iff i + j < n
        auto vx = mipp::loadu<mipp::Z>(m, x + i); // inactive lanes are not read (set to 0)
        auto vy = mipp::loadu<mipp::Z>(m, y + i);
        mipp::storeu<mipp::M>(m, y + i, mipp::fmadd(va, vx, vy)); // inactive lanes are not written
    }
}
// --8<-- [end:masked_tail]

static void masked_tail()
{
    const int N = mipp::N<float>();
    for (int n = 0; n <= 3 * N + 1 && n + 1 < DOC_BUF; n++) {
        float x[DOC_BUF], y[DOC_BUF];
        for (int i = 0; i < DOC_BUF; i++) { x[i] = 2.f; y[i] = 1.f; }
        saxpy((std::size_t)n, 3.f, x, y);
        for (int i = 0; i < n; i++)
            DOC_CHECK(y[i] == 7.f);
        DOC_CHECK(y[n] == 1.f); // the element after the end is not written
    }
}

int main()
{
    fill();
    auto_deduction();
    explicit_params();
    masked();
    masked_tail();
    return doc_status();
}

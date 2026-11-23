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
    auto a = mipp::load<float>(ptr_a); // Deduced as mipp::vd<float, 1, DEFAULT_ISA>
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
    auto zeroes = mipp::set0<double, 2>();       // mipp::vd<double, 2>
    auto scalar_val = mipp::set1<int32_t>(42);   // mipp::vd<int32_t, 1>
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

// Introduction: shorter namespace through an alias
static void namespace_alias()
{
    const float* ptr_a = A;
    const float* ptr_b = B;
    // --8<-- [start:namespace_alias]
    namespace mi = mipp; // once, in your own code (namespace or block scope)

    mi::vd<float> a = mi::load<float>(ptr_a);
    mi::vd<float> b = mi::load<float>(ptr_b);
    mi::vd<float> c = mi::add(a, b);
    // --8<-- [end:namespace_alias]
    mipp::storeu(OUT, c);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(OUT[i] == A[i] + B[i]);
}

// §3.6: masked operation
static void masked()
{
    mipp::vd<float> a = mipp::load<float>(A);
    mipp::vd<float> b = mipp::load<float>(B);
    mipp::vm<float> m = mipp::cmplt(a, b);
    // --8<-- [start:masked]
    mipp::vd<float> c = mipp::add<mipp::M, float>(m, a, b); // res[i] = m[i] ? a[i] + b[i] : a[i]
    // --8<-- [end:masked]
    mipp::storeu(OUT, c);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(OUT[i] == (A[i] < B[i] ? A[i] + B[i] : A[i]));
}

// §5: remainder handled with masked memory accesses
// --8<-- [start:masked_tail]
// y[i] = x[i] > 0 ? x[i] : alpha * x[i]
void leaky_relu(std::size_t n, float alpha, const float* x, float* y)
{
    constexpr std::size_t N = mipp::N<float>();
    const mipp::vd<float> vzero  = mipp::set1<float>(0.f);
    const mipp::vd<float> valpha = mipp::set1<float>(alpha);

    std::size_t i = 0;
    for (; i + N <= n; i += N) {
        mipp::vd<float> vx  = mipp::loadu<float>(x + i);
        mipp::vm<float> pos = mipp::cmpgt(vx, vzero);
        mipp::storeu(y + i, mipp::select(pos, vx, mipp::mul(vx, valpha)));
    }

    if (i < n) { // fewer than N elements left
        int32_t active[N];
        for (std::size_t j = 0; j < N; j++)
            active[j] = (i + j < n);
        mipp::vm<float> m   = mipp::set_k<float>(active);      // lane j active iff i + j < n
        mipp::vd<float> vx  = mipp::loadu<mipp::Z>(m, x + i); // inactive lanes are not read (set to 0)
        mipp::vm<float> pos = mipp::cmpgt(vx, vzero);
        mipp::storeu<mipp::M>(m, y + i, mipp::select(pos, vx, mipp::mul(vx, valpha))); // inactive lanes are not written
    }
}
// --8<-- [end:masked_tail]

static void masked_tail()
{
    const int N = mipp::N<float>();
    for (int n = 0; n <= 3 * N + 1 && n + 1 < DOC_BUF; n++) {
        float x[DOC_BUF], y[DOC_BUF];
        for (int i = 0; i < DOC_BUF; i++) { x[i] = (i % 2) ? 2.f : -2.f; y[i] = 99.f; }
        leaky_relu((std::size_t)n, 0.1f, x, y);
        for (int i = 0; i < n; i++)
            DOC_CHECK(y[i] == ((i % 2) ? 2.f : -0.2f));
        DOC_CHECK(y[n] == 99.f); // the element after the end is not written
    }
}

int main()
{
    fill();
    auto_deduction();
    explicit_params();
    namespace_alias();
    masked();
    masked_tail();
    return doc_status();
}

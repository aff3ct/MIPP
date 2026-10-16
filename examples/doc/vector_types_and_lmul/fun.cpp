#include <cstddef>
#include <cstdint>
#include <cstring>
#include <mipp.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF];
DOC_ALIGNED static float P[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        B[i] = (float)(i % 5) - 2.f;
        P[i] = -2.7f + 1.3f * (float)i; // -2.7, -1.4, -0.1, 1.2, ...
        OUT[i] = 0.f;
    }
}

// §2.2: element capacity
static void capacity()
{
    // --8<-- [start:capacity]
    constexpr int n_f32_m1 = mipp::N<float, 1>(); // 8 on AVX2 (256-bit / 32-bit * 1)
    constexpr int n_f32_m4 = mipp::N<float, 4>(); // 32 on AVX2 (8 * 4)
    // --8<-- [end:capacity]
    DOC_CHECK(n_f32_m4 == 4 * n_f32_m1);
    DOC_CHECK(n_f32_m1 * sizeof(float) == mipp::req_alignment());
}

// §3: tip, kernels parameterized by LMUL
// --8<-- [start:kernel]
template <typename T, int LMUL = 1>
void compute_kernel(const T* in, T* out, size_t n);
// --8<-- [end:kernel]

// §4: the same loop on half-vectors
static void d2_loop()
{
    const float* in_a = A;
    const float* in_b = B;
    float* out = OUT;
    const size_t n = 100;
    // --8<-- [start:d2_loop]
#ifdef MIPP_LDIV_2
constexpr size_t n_half = mipp::N<float, -2>();
for (size_t i = 0; i + n_half <= n; i += n_half) {
    mipp::rvd<float, -2> a = mipp::loadu<float, -2>(in_a + i);
    mipp::rvd<float, -2> b = mipp::loadu<float, -2>(in_b + i);
    mipp::rvd<float, -2> c = mipp::add(a, b);
    mipp::storeu(out + i, c);
}
#endif
    // --8<-- [end:d2_loop]
#ifdef MIPP_LDIV_2
    for (size_t i = 0; i < (n / n_half) * n_half; i++)
        DOC_CHECK(out[i] == A[i] + B[i]);
#else
    (void)in_a; (void)in_b; (void)out; (void)n;
#endif
}

// §4.1: availability guard
static void d2_guard()
{
    // --8<-- [start:d2_guard]
#ifdef MIPP_LDIV_2
    mipp::rvd<float, -2> h = mipp::set0<float, -2>();
#endif
    // --8<-- [end:d2_guard]
#ifdef MIPP_LDIV_2
    mipp::storeu(OUT, h);
    for (int i = 0; i < (int)mipp::N<float, -2>(); i++)
        DOC_CHECK(OUT[i] == 0.f);
#endif
}

// §5: type conversions
static void conversions()
{
    const float* ptr = P;
    // --8<-- [start:conversions]
    mipp::rvd<float>   v  = mipp::loadu<float>(ptr);  // {-2.7, -1.4, -0.1, 1.2, ...}
    mipp::rvd<int32_t> vb = mipp::cast_int32(v);      // {0xC02CCCCD, ...}: IEEE-754 bit patterns
    mipp::rvd<int32_t> vi = mipp::cvt_int32(v);       // {-2, -1, 0, 1, ...}: truncation
    mipp::rvd<double, 2> vw = mipp::wcvt_float64(v);  // {-2.7, -1.4, ...}: every element, in a register of LMUL 2
    // --8<-- [end:conversions]
    int32_t b[DOC_BUF], t[DOC_BUF];
    double w[DOC_BUF];
    mipp::storeu(b, vb);
    mipp::storeu(t, vi);
    mipp::storeu(w, vw);
    DOC_CHECK((uint32_t)b[0] == 0xC02CCCCDu);
    for (int i = 0; i < (int)mipp::N<float>(); i++) {
        int32_t bits;
        std::memcpy(&bits, &P[i], sizeof(bits));
        DOC_CHECK(b[i] == bits);
        DOC_CHECK(t[i] == (int32_t)P[i]);
    }
    DOC_CHECK(t[0] == -2 && t[1] == -1 && t[2] == 0 && t[3] == 1);
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(w[i] == (double)P[i]);
}

// §5.4: changing the LMUL
static void changing_lmul()
{
    const float* ptr = P;
    // --8<-- [start:changing_lmul]
    mipp::rvd<float>     a  = mipp::loadu<float>(ptr);
    mipp::rvd<float>     b  = mipp::loadu<float>(ptr + mipp::N<float>());
    mipp::rvd<float, 2>  ab = mipp::combine(a, b);          // {a, b}: twice as many elements
    mipp::rvd<float>     lo = mipp::low(ab);                // == a
    mipp::rvd<float>     hi = mipp::high(ab);               // == b
    mipp::rvd<double, 2> vw = mipp::wcvt_float64(a);        // a as double, in a register of LMUL 2
    mipp::rvd<float>     vn = mipp::ncvt_float32(vw);       // and back to float: == a
    // --8<-- [end:changing_lmul]
    float t[DOC_BUF], l[DOC_BUF], h[DOC_BUF], n[DOC_BUF];
    mipp::storeu(t, ab);
    mipp::storeu(l, lo);
    mipp::storeu(h, hi);
    mipp::storeu(n, vn);
    const int N = (int)mipp::N<float>();
    for (int i = 0; i < N; i++) {
        DOC_CHECK(t[i] == P[i] && t[i + N] == P[i + N]);
        DOC_CHECK(l[i] == P[i] && h[i] == P[i + N]);
        DOC_CHECK(n[i] == P[i]);
    }
}

int main()
{
    fill();
    capacity();
    d2_loop();
    d2_guard();
    conversions();
    changing_lmul();
    return doc_status();
}

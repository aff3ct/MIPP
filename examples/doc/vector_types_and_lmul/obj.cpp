#include <cstddef>
#include <cstdint>
#include <cstring>
#include <mipp_obj.hpp>

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
    constexpr int n_f32_m1 = mipp::Rvd<float, 1>::N(); // 8 on AVX2 (256-bit / 32-bit * 1)
    constexpr int n_f32_m4 = mipp::Rvd<float, 4>::N(); // 32 on AVX2 (8 * 4)
    // --8<-- [end:capacity]
    DOC_CHECK(n_f32_m4 == 4 * n_f32_m1);
    DOC_CHECK(n_f32_m1 * sizeof(float) == mipp::req_alignment());
}

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
    mipp::Rvd<float, -2> a = mipp::loadu_obj<float, -2>(in_a + i);
    mipp::Rvd<float, -2> b = mipp::loadu_obj<float, -2>(in_b + i);
    mipp::Rvd<float, -2> c = a + b;
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
    mipp::Rvd<float, -2> h = mipp::set0_obj<float, -2>();
#endif
    // --8<-- [end:d2_guard]
#ifdef MIPP_LDIV_2
    for (int i = 0; i < mipp::Rvd<float, -2>::N(); i++)
        DOC_CHECK(h[i] == 0.f);
#endif
}

// §5: type conversions
static void conversions()
{
    const float* ptr = P;
    // --8<-- [start:conversions]
    mipp::Rvd<float>   v  = mipp::loadu_obj<float>(ptr); // {-2.7, -1.4, -0.1, 1.2, ...}
    mipp::Rvd<int32_t> vb = mipp::cast<int32_t>(v);      // {0xC02CCCCD, ...}: IEEE-754 bit patterns
    mipp::Rvd<int32_t> vi = mipp::cvt<int32_t>(v);       // {-2, -1, 0, 1, ...}: truncation
    mipp::Rvd<double>  vw = mipp::wcvt<double>(v);       // {-2.7, -1.4, ...}: lower half only
    // --8<-- [end:conversions]
    DOC_CHECK((uint32_t)vb[0] == 0xC02CCCCDu);
    for (int i = 0; i < mipp::Rvd<float>::N(); i++) {
        int32_t bits;
        std::memcpy(&bits, &P[i], sizeof(bits));
        DOC_CHECK(vb[i] == bits);
        DOC_CHECK(vi[i] == (int32_t)P[i]);
    }
    DOC_CHECK(vi[0] == -2 && vi[1] == -1 && vi[2] == 0 && vi[3] == 1);
    for (int i = 0; i < mipp::Rvd<double>::N(); i++)
        DOC_CHECK(vw[i] == (double)P[i]);
}

int main()
{
    fill();
    capacity();
    d2_loop();
    d2_guard();
    conversions();
    return doc_status();
}

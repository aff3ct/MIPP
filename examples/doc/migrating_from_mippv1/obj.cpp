#include <cmath>
#include <cstddef>
#include <cstdint>
// --8<-- [start:includes]
#include <mipp_obj.hpp>
// --8<-- [end:includes]

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float X[DOC_BUF];
DOC_ALIGNED static float Y[DOC_BUF];
DOC_ALIGNED static uint32_t IDX[DOC_BUF];
DOC_ALIGNED static int8_t I8[DOC_BUF];
DOC_ALIGNED static int32_t I32[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)i;
        B[i] = 100.f + (float)i;
        X[i] = (float)(i % 7) - 3.f;
        Y[i] = -1.f;
        IDX[i] = (uint32_t)((int)mipp::N<float>() - 1 - (i % (int)mipp::N<float>()));
        I8[i] = (int8_t)((i % 2) ? 100 : -100);
        I32[i] = (i % 2) ? 70000 : -70000;
    }
}

// §2: the same loop with the objects of MIPPv2
// --8<-- [start:loop]
// y[i] = x[i] < 0 ? alpha * x[i] : x[i], n being a multiple of N
void leaky_relu(std::size_t n, float alpha, const float* x, float* y)
{
    constexpr std::size_t N = mipp::Vd<float>::N();
    for (std::size_t i = 0; i < n; i += N) {
        mipp::Vd<float> vx(&x[i]);                            // unaligned load
        mipp::Vm<float> m  = vx < 0.f;                        // the mask is typed by the element type
        mipp::Vd<float> vy = mipp::select(m, vx * alpha, vx); // m ? vx * alpha : vx
        mipp::storeu(&y[i], vy);                              // free function, unaligned store
    }
}
// --8<-- [end:loop]

static void loop()
{
    const std::size_t n = 4 * mipp::N<float>();
    leaky_relu(n, 0.5f, X, Y);
    for (std::size_t i = 0; i < n; i++) DOC_CHECK(Y[i] == (X[i] < 0.f ? 0.5f * X[i] : X[i]));
}

// §3: same names, other results
static void saturation()
{
    // --8<-- [start:saturation]
    mipp::Vd<int8_t> a(int8_t(100));
    mipp::Vd<int8_t> w = a + a;            // -56: wraps, as int8_t arithmetic in C (MIPPv1: 127)
    mipp::Vd<int8_t> s = mipp::adds(a, a); // 127: saturates, as MIPPv1
    int8_t hw = mipp::hadd(s);             // sum of the lanes, wraps
    int8_t hs = mipp::hadds(s);            // 127: saturates, as MIPPv1
    // --8<-- [end:saturation]
    const int n = (int)mipp::N<int8_t>();
    for (int i = 0; i < n; i++) DOC_CHECK(w[i] == -56 && s[i] == 127);
    DOC_CHECK(hw == (int8_t)(127 * n) && hs == 127);
}

static void shift()
{
    // --8<-- [start:shift]
    mipp::Vd<int32_t> a(-16);
    mipp::Vd<int32_t> ar = a >> 2;                                             // -4: arithmetic shift
    mipp::Vd<int32_t> lg = mipp::rshiftl(a, 2);                               // 0x3FFFFFFC: logical, as MIPPv1
    // --8<-- [end:shift]
    DOC_CHECK(ar[0] == -4 && lg[0] == 0x3FFFFFFC);
}

static void conversion()
{
    // --8<-- [start:conversion]
    mipp::Vd<float> f(2.7f), h(2.5f);
    mipp::Vd<int32_t> t = mipp::cvt<int32_t>(f);                  // 2: truncates, as a C cast (MIPPv1: 3)
    mipp::Vd<int32_t> r = mipp::cvt<int32_t>(mipp::roundeven(f)); // 3: rounds first, as MIPPv1
    mipp::Vd<float>   a = mipp::round(h);                         // 3: a tie goes away from zero
    mipp::Vd<float>   e = mipp::roundeven(h);                     // 2: a tie goes to the even integer, as MIPPv1
    // --8<-- [end:conversion]
    DOC_CHECK(t[0] == 2 && r[0] == 3 && a[0] == 3.f && e[0] == 2.f);
    DOC_CHECK(mipp::round(mipp::Vd<float>(-0.5f))[0] == -1.f && mipp::roundeven(mipp::Vd<float>(-0.5f))[0] == 0.f);
    DOC_CHECK(mipp::cvt<int32_t>(mipp::roundeven(mipp::Vd<float>(3.5f)))[0] == 4);
}

static void signs()
{
    // --8<-- [start:signs]
    mipp::Vd<float> a(-3.f), s(-1.f);
    mipp::Vd<float> x = mipp::xorsign(a, s);  //  3: sign of a flipped where s is negative (copysign of MIPPv1)
    mipp::Vd<float> c = mipp::copysign(a, s); // -3: magnitude of a, sign of s (as std::copysign)
    mipp::Vm<float> n = mipp::signbit(a);     // sign bit set: true for -0.0 too (sign of MIPPv1: a < 0)
    // --8<-- [end:signs]
    DOC_CHECK(x[0] == 3.f && c[0] == -3.f && n[0]);
    DOC_CHECK(mipp::signbit(mipp::Vd<float>(-0.f))[0] && !(mipp::Vd<float>(-0.f) < 0.f)[0]);
    // div2 / div4 of negative integers: arithmetic shift (MIPPv1: toward zero, -3 and -1)
    DOC_CHECK(mipp::div2(mipp::Vd<int32_t>(-7))[0] == -4 && mipp::div4(mipp::Vd<int32_t>(-7))[0] == -2);
}

// §4: correspondences
static void masked()
{
    mipp::Vd<float> a(A), b(B), src(X);
    // --8<-- [start:masked]
    mipp::Vm<float> m = a < 2.f;
    mipp::Vd<float> r = mipp::mul<mipp::S>(m, src, a, b); // m ? a * b : src   (mipp::mask<float, mipp::mul>)
    mipp::Vd<float> z = mipp::mul<mipp::Z>(m, a, b);      // m ? a * b : 0     (mipp::maskz<float, mipp::mul>)
    // --8<-- [end:masked]
    for (int i = 0; i < (int)mipp::N<float>(); i++) {
        DOC_CHECK(r[i] == (A[i] < 2.f ? A[i] * B[i] : X[i]));
        DOC_CHECK(z[i] == (A[i] < 2.f ? A[i] * B[i] : 0.f));
    }
}

static void halves()
{
    mipp::Vd<int8_t> v8(I8);
    mipp::Vd<int32_t> a32(I32), b32(I32);
    // --8<-- [start:halves]
    mipp::Vd<int8_t, -2> lo = v8.lo();                        // half register (mipp::Reg_2<int8_t>)
    mipp::Vd<int16_t> w = mipp::wcvt<int16_t>(lo);            // widening (cvt of a Reg_2)
    mipp::Vd<int16_t> p = mipp::pack<int16_t>(a32, b32);      // narrowing with saturation (pack)
    mipp::Vd<int8_t> back = mipp::combine(v8.lo(), v8.hi()); // two halves in a register
    // --8<-- [end:halves]
    const int n16 = (int)mipp::N<int16_t>();
    for (int i = 0; i < n16; i++) DOC_CHECK(w[i] == I8[i]);
    for (int i = 0; i < n16; i++) DOC_CHECK(p[i] == ((i % 2) ? 32767 : -32768));
    for (int i = 0; i < (int)mipp::N<int8_t>(); i++) DOC_CHECK(back[i] == I8[i]);
}

static void rearrangements()
{
    mipp::Vd<float> a(A), b(B);
    mipp::Vd<uint32_t> idx(IDX); // N-1, ..., 0
    // --8<-- [start:rearrangements]
    constexpr int N = mipp::Vd<float>::N();
    mipp::Vd<float> l = mipp::rotate(a, 1);     // a1 ... a[N-1] a0     (lrot)
    mipp::Vd<float> r = mipp::rotate(a, N - 1); // a[N-1] a0 ... a[N-2] (rrot)
    mipp::Vd<float> s = mipp::slide(a, b, 1);   // a1 ... a[N-1] b0     (combine<1>)
    mipp::Vd<float> z = mipp::ziplo(a, b);      // a0 b0 a1 b1 ...      (interleavelo)
    mipp::Vd<float> p = mipp::permute(a, idx);  // a[idx[i]]            (cmask + shuff)
    // --8<-- [end:rearrangements]
    for (int i = 0; i < N; i++) {
        DOC_CHECK(l[i] == A[(i + 1) % N] && r[i] == A[(i + N - 1) % N]);
        DOC_CHECK(s[i] == (i + 1 < N ? A[i + 1] : B[i + 1 - N]));
        DOC_CHECK(z[i] == ((i % 2) ? B[i / 2] : A[i / 2]));
        DOC_CHECK(p[i] == A[N - 1 - i]);
    }
}

static void complex_numbers()
{
    // --8<-- [start:complex]
    mipp::Vd<float> za(A), zb(B);             // {re0, im0, re1, im1, ...}: N / 2 complex numbers
    mipp::Vd<float> zc = mipp::cmul(za, zb);  // complex products
    mipp::Vd<float> n2 = mipp::cnorm(za);     // re^2 + im^2, in both lanes of each pair (norm)
    // --8<-- [end:complex]
    for (int i = 0; i + 1 < (int)mipp::N<float>(); i += 2) {
        DOC_CHECK(zc[i] == A[i] * B[i] - A[i + 1] * B[i + 1]);
        DOC_CHECK(zc[i + 1] == A[i] * B[i + 1] + A[i + 1] * B[i]);
        DOC_CHECK(n2[i] == A[i] * A[i] + A[i + 1] * A[i + 1] && n2[i + 1] == n2[i]);
    }
}

static void reductions()
{
    mipp::Vd<float> a(A);
    mipp::Vd<int32_t> x(0xF0), y(0x0F);
    // --8<-- [start:reductions]
    float vmax  = mipp::reduce(a, mipp::op::max());       // mipp::Reduction<float, mipp::max>::sapply(r)
    float total = mipp::reduce(B, 100, mipp::op::add());  // ...::apply(B, 100), for any number of elements
    bool  zero  = mipp::none(mipp::tovm(x & y));          // mipp::testz(r1, r2): no bit in common
    // --8<-- [end:reductions]
    float ref = 0.f;
    for (int i = 0; i < 100; i++) ref += B[i];
    DOC_CHECK(vmax == A[mipp::N<float>() - 1]);
    DOC_CHECK(std::fabs(total - ref) <= 1e-3f * ref);
    DOC_CHECK(zero && !mipp::none(mipp::tovm(x & x)));
}

int main()
{
    fill();
    loop();
    saturation();
    shift();
    conversion();
    signs();
    masked();
    halves();
    rearrangements();
    complex_numbers();
    reductions();
    return doc_status();
}

#include <cstdint>
#include <mipp_obj.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float X[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)i;
        B[i] = 100.f + (float)i;
        X[i] = (float)(i % 7) - 3.f;
    }
}

// §2: named rearrangements
static void named()
{
    // --8<-- [start:named]
    mipp::Rvd<float> a(A);
    mipp::Rvd<float> b(B);
    mipp::Rvd<float> r = mipp::reverse(a);                                         // a[N-1] ... a[0]
    mipp::Rvd<float, 2> z = mipp::combine(mipp::zip_lo(a, b), mipp::zip_hi(a, b)); // a0 b0 a1 b1 ...
    mipp::Rvd<float> e = mipp::unzip_even(z.low(), z.high());                      // a again
    mipp::Rvd<float> o = mipp::unzip_odd(z.low(), z.high());                       // b again
    // --8<-- [end:named]
    const int n = (int)mipp::N<float>();
    for (int i = 0; i < n; i++) DOC_CHECK(r[i] == A[n - 1 - i]);
    for (int i = 0; i < 2 * n; i++) DOC_CHECK(z[i] == ((i % 2) ? B[i / 2] : A[i / 2]));
    for (int i = 0; i < n; i++) DOC_CHECK(e[i] == A[i] && o[i] == B[i]);
}

// §3: lanes moved by a number of lanes
static void slide()
{
    mipp::Rvd<float> a(A);
    mipp::Rvd<float> b(B);
    // --8<-- [start:slide]
    mipp::Rvd<float> s = mipp::slide(a, b, 1);       // a1 ... a[N-1] b0
    mipp::Rvd<float> t = mipp::rotate(a, 1);         // a1 ... a[N-1] a0
    mipp::Rvd<float> u = mipp::broadcast_lane(a, 2); // a2 a2 ... a2
    // --8<-- [end:slide]
    const int n = (int)mipp::N<float>();
    for (int i = 0; i < n; i++) DOC_CHECK(s[i] == (i + 1 < n ? A[i + 1] : B[0]));
    for (int i = 0; i < n; i++) DOC_CHECK(t[i] == A[(i + 1) % n]);
    for (int i = 0; i < n; i++) DOC_CHECK(u[i] == A[2]);
}

// §4: interleaved data
static void interleaved()
{
    // --8<-- [start:interleaved]
    // N pairs (re, im): the real parts in the lower half of the LMUL 2 register, the imaginary ones in the upper half
    mipp::Rvd<float, 2> c = mipp::load_interleaved2_obj<float, 2>(X);
    mipp::Rvd<float> re = c.low();
    mipp::Rvd<float> im = c.high();
    mipp::Rvd<float> mag2 = mipp::fmadd(re, re, im * im); // re^2 + im^2
    // --8<-- [end:interleaved]
    const int n = (int)mipp::N<float>();
    for (int i = 0; i < n; i++) DOC_CHECK(mag2[i] == X[2 * i] * X[2 * i] + X[2 * i + 1] * X[2 * i + 1]);
}

int main()
{
    fill();
    named();
    slide();
    interleaved();
    return doc_status();
}

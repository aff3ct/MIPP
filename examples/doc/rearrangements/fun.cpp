#include <cstdint>
#include <mipp.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float X[DOC_BUF];
DOC_ALIGNED static float O1[DOC_BUF];
DOC_ALIGNED static float O2[DOC_BUF];

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
    mipp::rvd<float> a = mipp::load<float>(A);
    mipp::rvd<float> b = mipp::load<float>(B);
    mipp::rvd<float> r = mipp::reverse(a);                                  // a[N-1] ... a[0]
    mipp::rvd<float, 2> z = mipp::combine(mipp::zip_lo(a, b), mipp::zip_hi(a, b)); // a0 b0 a1 b1 ...
    mipp::rvd<float> e = mipp::unzip_even(mipp::low(z), mipp::high(z));     // a again
    mipp::rvd<float> o = mipp::unzip_odd(mipp::low(z), mipp::high(z));      // b again
    // --8<-- [end:named]
    const int n = (int)mipp::N<float>();
    mipp::store(O1, r);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[n - 1 - i]);
    mipp::storeu(O1, z);
    for (int i = 0; i < 2 * n; i++) DOC_CHECK(O1[i] == ((i % 2) ? B[i / 2] : A[i / 2]));
    mipp::store(O1, e);
    mipp::store(O2, o);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[i] && O2[i] == B[i]);
}

// §3: lanes moved by a number of lanes
static void slide()
{
    mipp::rvd<float> a = mipp::load<float>(A);
    mipp::rvd<float> b = mipp::load<float>(B);
    // --8<-- [start:slide]
    mipp::rvd<float> s = mipp::slide(a, b, 1);       // a1 ... a[N-1] b0
    mipp::rvd<float> t = mipp::rotate(a, 1);         // a1 ... a[N-1] a0
    mipp::rvd<float> u = mipp::broadcast_lane(a, 2); // a2 a2 ... a2
    // --8<-- [end:slide]
    const int n = (int)mipp::N<float>();
    mipp::store(O1, s);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == (i + 1 < n ? A[i + 1] : B[0]));
    mipp::store(O1, t);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[(i + 1) % n]);
    mipp::store(O1, u);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[2]);
}

// §4: interleaved data
static void interleaved()
{
    // --8<-- [start:interleaved]
    // N pairs (re, im): the real parts in the lower half of the LMUL 2 register, the imaginary ones in the upper half
    mipp::rvd<float, 2> c = mipp::load_interleaved2<float, 2>(X);
    mipp::rvd<float> re = mipp::low(c);
    mipp::rvd<float> im = mipp::high(c);
    mipp::rvd<float> mag2 = mipp::fmadd(re, re, mipp::mul(im, im)); // re^2 + im^2
    // --8<-- [end:interleaved]
    const int n = (int)mipp::N<float>();
    mipp::store(O1, mag2);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == X[2 * i] * X[2 * i] + X[2 * i + 1] * X[2 * i + 1]);
}

int main()
{
    fill();
    named();
    slide();
    interleaved();
    return doc_status();
}

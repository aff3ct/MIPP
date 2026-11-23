#include <cstdint>
#include <mipp_obj.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float X[DOC_BUF];
DOC_ALIGNED static uint32_t IDX[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF + 64]; // the filter of §6 writes up to one register past the count

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)i;
        B[i] = 100.f + (float)i;
        X[i] = (float)(i % 7) - 3.f;
        IDX[i] = (uint32_t)((i * 3 + 1) % (int)mipp::N<float>());
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
    // --8<-- [start:immediates]
    int32_t k = n / 2;                         // a variable: the dynamic body
    mipp::Rvd<float> v = mipp::slide(a, b, k);
    mipp::Rvd<float> w = mipp::slide<2>(a, b); // a constant, checked at compile time
    // --8<-- [end:immediates]
    for (int i = 0; i < n; i++) DOC_CHECK(v[i] == (i + k < n ? A[i + k] : B[i + k - n]));
    for (int i = 0; i < n; i++) DOC_CHECK(w[i] == (i + 2 < n ? A[i + 2] : B[i + 2 - n]));
}

// §4: interleaved data
static void interleaved()
{
    // --8<-- [start:interleaved]
    // N pairs (re, im): the real parts in the lower half of the LMUL 2 register, the imaginary ones in the upper half
    mipp::Rvd<float, 2> c = mipp::loadu_unzip_obj<float, 2>(X);
    mipp::Rvd<float> re = c.low();
    mipp::Rvd<float> im = c.high();
    mipp::Rvd<float> mag2 = mipp::fmadd(re, re, im * im); // re^2 + im^2
    // --8<-- [end:interleaved]
    const int n = (int)mipp::N<float>();
    for (int i = 0; i < n; i++) DOC_CHECK(mag2[i] == X[2 * i] * X[2 * i] + X[2 * i + 1] * X[2 * i + 1]);
}

// §5: permutations
static void permutations()
{
    // --8<-- [start:permute]
    mipp::Rvd<float> a(A);
    mipp::Rvd<uint32_t> idx(IDX);                   // indices < N
    mipp::Rvd<float> p = mipp::permute(a, idx);     // a[idx[0]], a[idx[1]], ...
    // --8<-- [end:permute]
    const int n = (int)mipp::N<float>();
    for (int i = 0; i < n; i++) DOC_CHECK(p[i] == A[IDX[i]]);
}

// §6: compress
static void filter()
{
    const size_t n = DOC_BUF;
    // --8<-- [start:filter]
    // keeps the positive elements of X: OUT needs one register of margin (storeuf_compress)
    float* out = OUT;
    for (size_t i = 0; i < n; i += mipp::N<float>()) {
        mipp::Rvd<float> v(X + i);
        mipp::Rvm<float> m = v > 0.f;
        out += mipp::storeuf_compress(out, v, m);
    }
    // --8<-- [end:filter]
    size_t k = 0;
    for (size_t i = 0; i < n; i++)
        if (X[i] > 0.f) DOC_CHECK(OUT[k++] == X[i]);
    DOC_CHECK(out == OUT + k);
}

int main()
{
    fill();
    named();
    slide();
    interleaved();
    permutations();
    filter();
    return doc_status();
}

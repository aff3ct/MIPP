#include <cstdint>
#include <mipp.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float X[DOC_BUF];
DOC_ALIGNED static float O1[DOC_BUF];
DOC_ALIGNED static float O2[DOC_BUF];
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
    mipp::rvd<float> a = mipp::load<float>(A);
    mipp::rvd<float> b = mipp::load<float>(B);
    mipp::rvd<float> r = mipp::reverse(a);                                  // a[N-1] ... a[0]
    mipp::rvd<float, 2> z = mipp::combine(mipp::ziplo(a, b), mipp::ziphi(a, b)); // a0 b0 a1 b1 ...
    mipp::rvd<float> e = mipp::unziplo(mipp::lo(z), mipp::hi(z));           // a again
    mipp::rvd<float> o = mipp::unziphi(mipp::lo(z), mipp::hi(z));           // b again
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
    mipp::rvd<float> u = mipp::bcast(a, 2); // a2 a2 ... a2
    // --8<-- [end:slide]
    const int n = (int)mipp::N<float>();
    mipp::store(O1, s);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == (i + 1 < n ? A[i + 1] : B[0]));
    mipp::store(O1, t);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[(i + 1) % n]);
    mipp::store(O1, u);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[2]);
    // --8<-- [start:immediates]
    int32_t k = n / 2;                         // a variable: the dynamic body
    mipp::rvd<float> v = mipp::slide(a, b, k);
    mipp::rvd<float> w = mipp::slide<2>(a, b); // a constant, checked at compile time
    // --8<-- [end:immediates]
    mipp::store(O1, v);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == (i + k < n ? A[i + k] : B[i + k - n]));
    mipp::store(O1, w);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == (i + 2 < n ? A[i + 2] : B[i + 2 - n]));
}

// §4: interleaved data
static void interleaved()
{
    // --8<-- [start:interleaved]
    // N pairs (re, im): the real parts in the lower half of the LMUL 2 register, the imaginary ones in the upper half
    mipp::rvd<float, 2> c = mipp::loadu_unzip<float, 2>(X);
    mipp::rvd<float> re = mipp::lo(c);
    mipp::rvd<float> im = mipp::hi(c);
    mipp::rvd<float> mag2 = mipp::fmadd(re, re, mipp::mul(im, im)); // re^2 + im^2
    // --8<-- [end:interleaved]
    const int n = (int)mipp::N<float>();
    mipp::store(O1, mag2);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == X[2 * i] * X[2 * i] + X[2 * i + 1] * X[2 * i + 1]);
}

// §5: permutations
static void permutations()
{
    // --8<-- [start:permute]
    mipp::rvd<float> a = mipp::load<float>(A);
    mipp::rvd<uint32_t> idx = mipp::load<uint32_t>(IDX); // indices < N
    mipp::rvd<float> p = mipp::permute(a, idx);          // a[idx[0]], a[idx[1]], ...
    // --8<-- [end:permute]
    const int n = (int)mipp::N<float>();
    mipp::store(O1, p);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[IDX[i]]);
}

// §6: compress
static void filter()
{
    const size_t n = DOC_BUF;
    // --8<-- [start:filter]
    // keeps the positive elements of X: OUT needs one register of margin (storeuf_compress)
    float* out = OUT;
    for (size_t i = 0; i < n; i += mipp::N<float>()) {
        mipp::rvd<float> v = mipp::loadu<float>(X + i);
        mipp::rvm<float> m = mipp::cmpgt(v, 0.f);
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

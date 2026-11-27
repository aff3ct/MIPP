#include <cstddef>
#include <cstdint>
#include <vector>
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
    mipp::vd<float> a = mipp::load<float>(A);
    mipp::vd<float> b = mipp::load<float>(B);
    mipp::vd<float> r = mipp::reverse(a);                                   // a[N-1] ... a[0]
    mipp::vd<float, 2> z = mipp::combine(mipp::ziplo(a, b), mipp::ziphi(a, b)); // a0 b0 a1 b1 ...
    mipp::vd<float> e = mipp::unziplo(mipp::lo(z), mipp::hi(z));            // a again
    mipp::vd<float> o = mipp::unziphi(mipp::lo(z), mipp::hi(z));            // b again
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
    mipp::vd<float> a = mipp::load<float>(A);
    mipp::vd<float> b = mipp::load<float>(B);
    // --8<-- [start:slide]
    mipp::vd<float> s = mipp::slide(a, b, 1);        // a1 ... a[N-1] b0
    mipp::vd<float> t = mipp::rotate(a, 1);          // a1 ... a[N-1] a0
    mipp::vd<float> u = mipp::bcast(a, 2); // a2 a2 ... a2
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
    mipp::vd<float> v = mipp::slide(a, b, k);
    mipp::vd<float> w = mipp::slide<2>(a, b); // a constant, checked at compile time
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
    mipp::vd<float, 2> c = mipp::loadu_unzip<float, 2>(X);
    mipp::vd<float> re = mipp::lo(c);
    mipp::vd<float> im = mipp::hi(c);
    mipp::vd<float> mag2 = mipp::fmadd(re, re, mipp::mul(im, im)); // re^2 + im^2
    // --8<-- [end:interleaved]
    const int n = (int)mipp::N<float>();
    mipp::store(O1, mag2);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == X[2 * i] * X[2 * i] + X[2 * i + 1] * X[2 * i + 1]);
}

// §5: permutations
static void permutations()
{
    // --8<-- [start:permute]
    mipp::vd<float> a = mipp::load<float>(A);
    mipp::vd<uint32_t> idx = mipp::load<uint32_t>(IDX); // indices < N
    mipp::vd<float> p = mipp::permute(a, idx);           // a[idx[0]], a[idx[1]], ...
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
        mipp::vd<float> v = mipp::loadu<float>(X + i);
        mipp::vm<float> m = mipp::cmpgt(v, 0.f);
        out += mipp::storeuf_compress(out, v, m);
    }
    // --8<-- [end:filter]
    size_t k = 0;
    for (size_t i = 0; i < n; i++)
        if (X[i] > 0.f) DOC_CHECK(OUT[k++] == X[i]);
    DOC_CHECK(out == OUT + k);
}

// §7: transpositions
static void transpositions()
{
    const size_t n = mipp::N<float>();
    std::vector<float> m(n * n), mt(n * n);
    for (size_t i = 0; i < n * n; i++) m[i] = (float)i;
    // --8<-- [start:transpose]
    // m: a matrix of n x n floats (n = N<float>()), row-major; mt: its transpose
    mipp::vd<float> rows[mipp::N<float>()];
    for (size_t i = 0; i < n; i++) rows[i] = mipp::loadu<float>(&m[i * n]);
    mipp::transpose<float>(rows); // rows[i]: the column i of m
    for (size_t i = 0; i < n; i++) mipp::storeu(&mt[i * n], rows[i]);
    // --8<-- [end:transpose]
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++) DOC_CHECK(mt[i * n + j] == m[j * n + i]);

    std::vector<float> pts(4 * n), ref(4 * n);
    for (size_t i = 0; i < 4 * n; i++) pts[i] = ref[i] = (float)(i % 5) + 1.f;
    // --8<-- [start:transpose_b128]
    // n points (x, y, z, w), one after the other in memory: x, y and z divided by w
    mipp::vd<float> v[4];
    for (size_t i = 0; i < 4; i++) v[i] = mipp::loadu<float>(&pts[i * n]);
    mipp::transpose_b128<float>(v); // v[0]: x of n points, v[1]: y, v[2]: z, v[3]: w
    for (size_t c = 0; c < 3; c++) v[c] = mipp::div(v[c], v[3]);
    mipp::transpose_b128<float>(v); // back to (x, y, z, w)
    for (size_t i = 0; i < 4; i++) mipp::storeu(&pts[i * n], v[i]);
    // --8<-- [end:transpose_b128]
    for (size_t p = 0; p < n; p++)
        for (size_t c = 0; c < 4; c++)
            DOC_CHECK(pts[4 * p + c] == (c < 3 ? ref[4 * p + c] / ref[4 * p + 3] : ref[4 * p + 3]));
}

int main()
{
    fill();
    named();
    slide();
    interleaved();
    permutations();
    filter();
    transpositions();
    return doc_status();
}

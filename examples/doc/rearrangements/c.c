#include <stdint.h>
#include <mipp.h>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float X[DOC_BUF];
DOC_ALIGNED static float O1[DOC_BUF];
DOC_ALIGNED static float O2[DOC_BUF];
DOC_ALIGNED static uint32_t IDX[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF + 64]; /* the filter of §6 writes up to one register past the count */

static void fill(void)
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)i;
        B[i] = 100.f + (float)i;
        X[i] = (float)(i % 7) - 3.f;
        IDX[i] = (uint32_t)((i * 3 + 1) % (int)MIPP_N_FLOAT32);
    }
}

/* §2: named rearrangements */
static void named(void)
{
    // --8<-- [start:named]
    vd_float32_t a = mipp_load_float32(A);
    vd_float32_t b = mipp_load_float32(B);
    vd_float32_t r = mipp_reverse_float32(a);                                                        // a[N-1] ... a[0]
    vd_float32_m2_t z = mipp_combine_float32(mipp_ziplo_float32(a, b), mipp_ziphi_float32(a, b)); // a0 b0 a1 b1 ...
    vd_float32_t e = mipp_unziplo_float32(mipp_lo_float32_m2(z), mipp_hi_float32_m2(z));             // a again
    vd_float32_t o = mipp_unziphi_float32(mipp_lo_float32_m2(z), mipp_hi_float32_m2(z));             // b again
    // --8<-- [end:named]
    const int n = (int)MIPP_N_FLOAT32;
    mipp_store_float32(O1, r);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[n - 1 - i]);
    mipp_storeu_float32_m2(O1, z);
    for (int i = 0; i < 2 * n; i++) DOC_CHECK(O1[i] == ((i % 2) ? B[i / 2] : A[i / 2]));
    mipp_store_float32(O1, e);
    mipp_store_float32(O2, o);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[i] && O2[i] == B[i]);
}

/* §3: lanes moved by a number of lanes */
static void slide(void)
{
    vd_float32_t a = mipp_load_float32(A);
    vd_float32_t b = mipp_load_float32(B);
    // --8<-- [start:slide]
    vd_float32_t s = mipp_slide_float32(a, b, 1);        // a1 ... a[N-1] b0
    vd_float32_t t = mipp_rotate_float32(a, 1);          // a1 ... a[N-1] a0
    vd_float32_t u = mipp_bcast_float32(a, 2); // a2 a2 ... a2
    // --8<-- [end:slide]
    const int n = (int)MIPP_N_FLOAT32;
    mipp_store_float32(O1, s);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == (i + 1 < n ? A[i + 1] : B[0]));
    mipp_store_float32(O1, t);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[(i + 1) % n]);
    mipp_store_float32(O1, u);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[2]);
    // --8<-- [start:immediates]
    int32_t k = n / 2;                             // a variable: the dynamic body
    vd_float32_t v = mipp_slide_float32(a, b, k);
    vd_float32_t w = mipp_slide_float32(a, b, 2); // a constant: palignr, ext...
    // --8<-- [end:immediates]
    mipp_store_float32(O1, v);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == (i + k < n ? A[i + k] : B[i + k - n]));
    mipp_store_float32(O1, w);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == (i + 2 < n ? A[i + 2] : B[i + 2 - n]));
}

/* §4: interleaved data */
static void interleaved(void)
{
    // --8<-- [start:interleaved]
    // N pairs (re, im): the real parts in the lower half of the LMUL 2 register, the imaginary ones in the upper half
    vd_float32_m2_t c = mipp_loadu_unzip_float32_m2(X);
    vd_float32_t re = mipp_lo_float32_m2(c);
    vd_float32_t im = mipp_hi_float32_m2(c);
    vd_float32_t mag2 = mipp_fmadd_float32(re, re, mipp_mul_float32(im, im)); // re^2 + im^2
    // --8<-- [end:interleaved]
    const int n = (int)MIPP_N_FLOAT32;
    mipp_store_float32(O1, mag2);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == X[2 * i] * X[2 * i] + X[2 * i + 1] * X[2 * i + 1]);
}

/* §5: permutations */
static void permutations(void)
{
    // --8<-- [start:permute]
    vd_float32_t a = mipp_load_float32(A);
    vd_uint32_t idx = mipp_load_uint32(IDX);            // indices < N
    vd_float32_t p = mipp_permute_float32(a, idx);      // a[idx[0]], a[idx[1]], ...
    // --8<-- [end:permute]
    const int n = (int)MIPP_N_FLOAT32;
    mipp_store_float32(O1, p);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[IDX[i]]);
}

/* §6: compress */
static void filter(void)
{
    const size_t n = DOC_BUF;
    // --8<-- [start:filter]
    // keeps the positive elements of X: OUT needs one register of margin (storeuf_compress)
    float* out = OUT;
    for (size_t i = 0; i < n; i += MIPP_N_FLOAT32) {
        vd_float32_t v = mipp_loadu_float32(X + i);
        vm_float32_t m = mipp_cmpgt_float32(v, mipp_set0_float32());
        out += mipp_storeuf_compress_float32(out, v, m);
    }
    // --8<-- [end:filter]
    size_t k = 0;
    for (size_t i = 0; i < n; i++)
        if (X[i] > 0.f) DOC_CHECK(OUT[k++] == X[i]);
    DOC_CHECK(out == OUT + k);
}

int main(void)
{
    fill();
    named();
    slide();
    interleaved();
    permutations();
    filter();
    return doc_status();
}

#include <stdint.h>
#include <mipp.h>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float X[DOC_BUF];
DOC_ALIGNED static float O1[DOC_BUF];
DOC_ALIGNED static float O2[DOC_BUF];

static void fill(void)
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)i;
        B[i] = 100.f + (float)i;
        X[i] = (float)(i % 7) - 3.f;
    }
}

/* §2: named rearrangements */
static void named(void)
{
    // --8<-- [start:named]
    rvd_float32_t a = mipp_load_float32(A);
    rvd_float32_t b = mipp_load_float32(B);
    rvd_float32_t r = mipp_reverse_float32(a);                                                       // a[N-1] ... a[0]
    rvd_float32_m2_t z = mipp_combine_float32(mipp_zip_lo_float32(a, b), mipp_zip_hi_float32(a, b)); // a0 b0 a1 b1 ...
    rvd_float32_t e = mipp_unzip_even_float32(mipp_low_float32_m2(z), mipp_high_float32_m2(z));      // a again
    rvd_float32_t o = mipp_unzip_odd_float32(mipp_low_float32_m2(z), mipp_high_float32_m2(z));       // b again
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
    rvd_float32_t a = mipp_load_float32(A);
    rvd_float32_t b = mipp_load_float32(B);
    // --8<-- [start:slide]
    rvd_float32_t s = mipp_slide_float32(a, b, 1);       // a1 ... a[N-1] b0
    rvd_float32_t t = mipp_rotate_float32(a, 1);         // a1 ... a[N-1] a0
    rvd_float32_t u = mipp_broadcast_lane_float32(a, 2); // a2 a2 ... a2
    // --8<-- [end:slide]
    const int n = (int)MIPP_N_FLOAT32;
    mipp_store_float32(O1, s);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == (i + 1 < n ? A[i + 1] : B[0]));
    mipp_store_float32(O1, t);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[(i + 1) % n]);
    mipp_store_float32(O1, u);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == A[2]);
}

/* §4: interleaved data */
static void interleaved(void)
{
    // --8<-- [start:interleaved]
    // N pairs (re, im): the real parts in the lower half of the LMUL 2 register, the imaginary ones in the upper half
    rvd_float32_m2_t c = mipp_load_interleaved2_float32_m2(X);
    rvd_float32_t re = mipp_low_float32_m2(c);
    rvd_float32_t im = mipp_high_float32_m2(c);
    rvd_float32_t mag2 = mipp_fmadd_float32(re, re, mipp_mul_float32(im, im)); // re^2 + im^2
    // --8<-- [end:interleaved]
    const int n = (int)MIPP_N_FLOAT32;
    mipp_store_float32(O1, mag2);
    for (int i = 0; i < n; i++) DOC_CHECK(O1[i] == X[2 * i] * X[2 * i] + X[2 * i + 1] * X[2 * i + 1]);
}

int main(void)
{
    fill();
    named();
    slide();
    interleaved();
    return doc_status();
}

#include <math.h>
#include <mipp.h>

#include "doc_check.h"

DOC_ALIGNED static float Z[DOC_BUF];  /* re0 im0 re1 im1 ... */
DOC_ALIGNED static float W[DOC_BUF];
DOC_ALIGNED static float P[DOC_BUF];
DOC_ALIGNED static float Q[DOC_BUF];
DOC_ALIGNED static float S[DOC_BUF];
DOC_ALIGNED static float M[DOC_BUF];
DOC_ALIGNED static float AR[DOC_BUF]; /* split layout: the real parts... */
DOC_ALIGNED static float AI[DOC_BUF]; /* ... and the imaginary parts */
DOC_ALIGNED static float BR[DOC_BUF];
DOC_ALIGNED static float BI[DOC_BUF];
DOC_ALIGNED static float PR[DOC_BUF];
DOC_ALIGNED static float PI[DOC_BUF];

static void fill(void)
{
    for (int i = 0; i < DOC_BUF; i++) {
        Z[i] = (float)(i % 7) - 3.f;
        W[i] = 1.f + (float)(i % 5); /* no zero divisor */
        AR[i] = Z[i];
        AI[i] = 0.5f * (float)(i % 3);
        BR[i] = W[i];
        BI[i] = (float)(i % 4) - 2.f;
    }
}

static int close_to(float x, float ref)
{
    return fabsf(x - ref) <= 1e-4f * (1.f + fabsf(ref));
}

/* §2: interleaved layout */
static void interleaved(void)
{
    // --8<-- [start:interleaved]
    vd_float32_t a = mipp_load_float32(Z);          // re0 im0 re1 im1 ...
    vd_float32_t b = mipp_load_float32(W);
    vd_float32_t p = mipp_cmul_float32(a, b);       // a * b
    vd_float32_t q = mipp_cdiv_float32(a, b);       // a / b
    vd_float32_t s = mipp_cfmadd_float32(a, b, p); // a * b + p
    vd_float32_t m = mipp_cabs_float32(a);          // |a|, in both lanes of each pair
    // --8<-- [end:interleaved]
    mipp_store_float32(P, p);
    mipp_store_float32(Q, q);
    mipp_store_float32(S, s);
    mipp_store_float32(M, m);
    for (int i = 0; i + 1 < (int)MIPP_N_FLOAT32; i += 2) {
        const float ar = Z[i], ai = Z[i + 1], br = W[i], bi = W[i + 1], d = br * br + bi * bi;
        DOC_CHECK(close_to(P[i], ar * br - ai * bi) && close_to(P[i + 1], ar * bi + ai * br));
        DOC_CHECK(close_to(Q[i], (ar * br + ai * bi) / d) && close_to(Q[i + 1], (ai * br - ar * bi) / d));
        DOC_CHECK(close_to(S[i], 2.f * P[i]) && close_to(S[i + 1], 2.f * P[i + 1]));
        DOC_CHECK(close_to(M[i], sqrtf(ar * ar + ai * ai)) && M[i + 1] == M[i]);
    }
}

/* §3: split layout */
static void split(void)
{
    // --8<-- [start:split]
    vd_float32_t ar = mipp_load_float32(AR), ai = mipp_load_float32(AI);
    vd_float32_t br = mipp_load_float32(BR), bi = mipp_load_float32(BI);
    vd_float32_t pr = mipp_fmsub_float32(ar, br, mipp_mul_float32(ai, bi)); // ar br - ai bi
    vd_float32_t pi = mipp_fmadd_float32(ar, bi, mipp_mul_float32(ai, br)); // ar bi + ai br
    // --8<-- [end:split]
    mipp_store_float32(PR, pr);
    mipp_store_float32(PI, pi);
    for (int i = 0; i < (int)MIPP_N_FLOAT32; i++)
        DOC_CHECK(close_to(PR[i], AR[i] * BR[i] - AI[i] * BI[i]) && close_to(PI[i], AR[i] * BI[i] + AI[i] * BR[i]));
}

int main(void)
{
    fill();
    interleaved();
    split();
    return doc_status();
}

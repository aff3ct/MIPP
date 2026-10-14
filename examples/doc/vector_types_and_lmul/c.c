#include <stdint.h>
#include <string.h>
#include <mipp.h>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF];
DOC_ALIGNED static float P[DOC_BUF];

static void fill(void)
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        B[i] = (float)(i % 5) - 2.f;
        P[i] = -2.7f + 1.3f * (float)i; /* -2.7, -1.4, -0.1, 1.2, ... */
        OUT[i] = 0.f;
    }
}

/* §2.2: element capacity */
static void capacity(void)
{
    /* --8<-- [start:capacity] */
    const int n_f32_m1 = MIPP_N_FLOAT32;    // 8 on AVX2 (256-bit / 32-bit * 1)
    const int n_f32_m4 = MIPP_N_FLOAT32_M4; // 32 on AVX2 (8 * 4)
    /* --8<-- [end:capacity] */
    DOC_CHECK(n_f32_m4 == 4 * n_f32_m1);
    DOC_CHECK((size_t)n_f32_m1 * sizeof(float) == (size_t)MIPP_RVD_SIZE_BYTE);
}

/* §4: the same loop on half-vectors */
static void d2_loop(void)
{
    const float* in_a = A;
    const float* in_b = B;
    float* out = OUT;
    const size_t n = 100;
    /* --8<-- [start:d2_loop] */
#ifdef MIPP_LDIV_2
const size_t n_half = MIPP_N_FLOAT32_D2;
for (size_t i = 0; i + n_half <= n; i += n_half) {
    rvd_float32_d2_t a = mipp_loadu_float32_d2(in_a + i);
    rvd_float32_d2_t b = mipp_loadu_float32_d2(in_b + i);
    rvd_float32_d2_t c = mipp_add_float32_d2(a, b);
    mipp_storeu_float32_d2(out + i, c);
}
#endif
    /* --8<-- [end:d2_loop] */
#ifdef MIPP_LDIV_2
    for (size_t i = 0; i < (n / MIPP_N_FLOAT32_D2) * MIPP_N_FLOAT32_D2; i++)
        DOC_CHECK(out[i] == A[i] + B[i]);
#else
    (void)in_a; (void)in_b; (void)out; (void)n;
#endif
}

/* §4.1: availability guard */
static void d2_guard(void)
{
    /* --8<-- [start:d2_guard] */
#ifdef MIPP_LDIV_2
    rvd_float32_d2_t h = mipp_set0_float32_d2();
#endif
    /* --8<-- [end:d2_guard] */
#ifdef MIPP_LDIV_2
    mipp_storeu_float32_d2(OUT, h);
    for (int i = 0; i < MIPP_N_FLOAT32_D2; i++)
        DOC_CHECK(OUT[i] == 0.f);
#endif
}

/* §5: type conversions */
static void conversions(void)
{
    const float* ptr = P;
    /* --8<-- [start:conversions] */
    rvd_float32_t v  = mipp_loadu_float32(ptr);       // {-2.7, -1.4, -0.1, 1.2, ...}
    rvd_int32_t   vb = mipp_cast_float32_int32(v);    // {0xC02CCCCD, ...}: IEEE-754 bit patterns
    rvd_int32_t   vi = mipp_cvt_float32_int32(v);     // {-2, -1, 0, 1, ...}: truncation
    rvd_float64_t vw = mipp_wcvt_float32_float64(v);  // {-2.7, -1.4, ...}: lower half only
    /* --8<-- [end:conversions] */
    int32_t b[DOC_BUF], t[DOC_BUF];
    double w[DOC_BUF];
    mipp_storeu_int32(b, vb);
    mipp_storeu_int32(t, vi);
    mipp_storeu_float64(w, vw);
    DOC_CHECK((uint32_t)b[0] == 0xC02CCCCDu);
    for (int i = 0; i < MIPP_N_FLOAT32; i++) {
        int32_t bits;
        memcpy(&bits, &P[i], sizeof(bits));
        DOC_CHECK(b[i] == bits);
        DOC_CHECK(t[i] == (int32_t)P[i]);
    }
    DOC_CHECK(t[0] == -2 && t[1] == -1 && t[2] == 0 && t[3] == 1);
    for (int i = 0; i < MIPP_N_FLOAT64; i++)
        DOC_CHECK(w[i] == (double)P[i]);
}

int main(void)
{
    fill();
    capacity();
    d2_loop();
    d2_guard();
    conversions();
    return doc_status();
}

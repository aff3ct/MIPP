#include <stdint.h>
#include <mipp.h>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF];
DOC_ALIGNED static int32_t I[DOC_BUF];
DOC_ALIGNED static int32_t CNT[DOC_BUF];
DOC_ALIGNED static int32_t IOUT[DOC_BUF];

static void fill(void)
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        B[i] = (float)(i % 5) - 2.f;
        I[i] = (i % 9) - 4;
        CNT[i] = i % 5;
    }
}

/* §2: registers and scalars */
static void forms(void)
{
    // --8<-- [start:forms]
    vd_float32_t va = mipp_load_float32(A);
    vd_float32_t vb = mipp_load_float32(B);
    vd_float32_t r1 = mipp_sub_vs_float32(va, 1.f);         // a - 1
    vd_float32_t r2 = mipp_sub_sv_float32(10.f, va);        // 10 - a
    vd_float32_t r3 = mipp_fmadd_vsv_float32(va, 2.f, vb); // a * 2 + b
    vm_float32_t m = mipp_cmplt_vs_float32(va, 0.f);        // a < 0
    // --8<-- [end:forms]
    const int n = (int)MIPP_N_FLOAT32;
    mipp_store_float32(OUT, r1);
    for (int i = 0; i < n; i++) DOC_CHECK(OUT[i] == A[i] - 1.f);
    mipp_store_float32(OUT, r2);
    for (int i = 0; i < n; i++) DOC_CHECK(OUT[i] == 10.f - A[i]);
    mipp_store_float32(OUT, r3);
    for (int i = 0; i < n; i++) DOC_CHECK(OUT[i] == A[i] * 2.f + B[i]);
    mipp_store_float32(OUT, mipp_select_float32(m, mipp_set1_float32(1.f), mipp_set0_float32()));
    for (int i = 0; i < n; i++) DOC_CHECK(OUT[i] == (A[i] < 0.f ? 1.f : 0.f));

    // --8<-- [start:masked]
    // merge masking keeps the register operand: m ? 10 - a : a
    vd_float32_t r4 = mipp_sub_sv_float32_mask(m, 10.f, va);
    // --8<-- [end:masked]
    mipp_store_float32(OUT, r4);
    for (int i = 0; i < n; i++) DOC_CHECK(OUT[i] == (A[i] < 0.f ? 10.f - A[i] : A[i]));
}

/* §4: shifts */
static void shifts(void)
{
    // --8<-- [start:shifts]
    vd_int32_t vi = mipp_load_int32(I);
    vd_int32_t vn = mipp_load_int32(CNT);             // a count per lane, in [0, 31]
    vd_int32_t s1 = mipp_lshift_int32(vi, vn);        // i << n, lane by lane
    vd_int32_t s2 = mipp_rshift_vs_int32(vi, 1);      // i >> 1, every lane
    // --8<-- [end:shifts]
    const int n = (int)MIPP_N_INT32;
    mipp_store_int32(IOUT, s1);
    for (int i = 0; i < n; i++) DOC_CHECK(IOUT[i] == (int32_t)((uint32_t)I[i] << CNT[i]));
    mipp_store_int32(IOUT, s2);
    for (int i = 0; i < n; i++) DOC_CHECK(IOUT[i] == (I[i] >> 1));
}

int main(void)
{
    fill();
    forms();
    shifts();
    return doc_status();
}

#include <stdint.h>
#include <string.h>
#include <mipp.h>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];
DOC_ALIGNED static float SRC[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF];

static void fill(void)
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        B[i] = (float)(i % 5) - 2.f;
        SRC[i] = 100.f + (float)i;
    }
}

/* Lane i of a float32 mask, as 0 or 1. */
static void lanes(rvm_float32_t m, int32_t* out)
{
    rvd_float32_t r = mipp_blend_float32(m, mipp_set1_float32(1.f), mipp_set0_float32());
    mipp_storeu_float32(OUT, r);
    for (int i = 0; i < MIPP_N_FLOAT32; i++)
        out[i] = OUT[i] != 0.f;
}

/* §2.1: the four variants */
static void variants(void)
{
    rvd_float32_t va = mipp_load_float32(A);
    rvd_float32_t vb = mipp_load_float32(B);
    rvd_float32_t vsrc = mipp_load_float32(SRC);
    /* --8<-- [start:variants] */
    // Mask generation via comparison:
    rvm_float32_t m = mipp_cmplt_float32(va, vb);

    // 1. Unmasked:
    rvd_float32_t res_u = mipp_add_float32(va, vb);

    // 2. Merge-Masked:
    rvd_float32_t res_m = mipp_add_float32_mask(m, va, vb);

    // 3. Zero-Masked:
    rvd_float32_t res_z = mipp_add_float32_maskz(m, va, vb);

    // 4. Source-Masked:
    rvd_float32_t res_s = mipp_add_float32_masks(m, vsrc, va, vb);
    /* --8<-- [end:variants] */
    float u[DOC_BUF], mm[DOC_BUF], z[DOC_BUF], s[DOC_BUF];
    mipp_storeu_float32(u, res_u);
    mipp_storeu_float32(mm, res_m);
    mipp_storeu_float32(z, res_z);
    mipp_storeu_float32(s, res_s);
    for (int i = 0; i < MIPP_N_FLOAT32; i++) {
        const int act = A[i] < B[i];
        DOC_CHECK(u[i] == A[i] + B[i]);
        DOC_CHECK(mm[i] == (act ? A[i] + B[i] : A[i]));
        DOC_CHECK(z[i] == (act ? A[i] + B[i] : 0.f));
        DOC_CHECK(s[i] == (act ? A[i] + B[i] : SRC[i]));
    }
}

/* §6.1: cast_k */
static void cast_k(void)
{
    rvd_float32_t va = mipp_load_float32(A);
    rvd_float32_t vb = mipp_load_float32(B);
    /* --8<-- [start:cast_k] */
    // C API: explicit from_to function identifier with _k suffix
    rvm_float32_t m_float = mipp_cmplt_float32(va, vb);
    rvm_int32_t   m_int   = mipp_cast_k_float32_int32(m_float);
    /* --8<-- [end:cast_k] */
    int32_t r[DOC_BUF];
    mipp_storeu_int32(r, mipp_blend_int32(m_int, mipp_set1_int32(1), mipp_set0_int32()));
    for (int i = 0; i < MIPP_N_INT32; i++)
        DOC_CHECK(r[i] == (A[i] < B[i]));
}

/* §6.2: tomsk */
static void tomsk(void)
{
    const float* ptr = A;
    /* --8<-- [start:tomsk] */
    // C API:
    rvd_float32_t raw_vector = mipp_load_float32(ptr);
    rvm_float32_t m = mipp_tomsk_float32(raw_vector);
    /* --8<-- [end:tomsk] */
    int32_t act[DOC_BUF];
    lanes(m, act);
    for (int i = 0; i < MIPP_N_FLOAT32; i++)
        DOC_CHECK(act[i] == (A[i] != 0.f)); /* +0.0f is the only inactive value of A */
}

/* §6.3: toreg */
static void toreg(void)
{
    rvd_float32_t va = mipp_load_float32(A);
    rvd_float32_t vb = mipp_load_float32(B);
    /* --8<-- [start:toreg] */
    // C API:
    rvm_float32_t m = mipp_cmpeq_float32(va, vb);
    rvd_float32_t mask_vector = mipp_toreg_float32(m);
    /* --8<-- [end:toreg] */
    uint32_t bits[DOC_BUF];
    mipp_storeu_float32(OUT, mask_vector);
    memcpy(bits, OUT, sizeof(bits));
    for (int i = 0; i < MIPP_N_FLOAT32; i++)
        DOC_CHECK(bits[i] == (A[i] == B[i] ? 0xFFFFFFFFu : 0u));
}

/* §6.4: blend */
static void blend(void)
{
    rvd_float32_t if_true = mipp_load_float32(A);
    rvd_float32_t if_false = mipp_load_float32(B);
    rvm_float32_t m = mipp_cmplt_float32(if_true, if_false);
    /* --8<-- [start:blend] */
    // C API: (mask, if_true, if_false)
    rvd_float32_t chosen = mipp_blend_float32(m, if_true, if_false);
    /* --8<-- [end:blend] */
    mipp_storeu_float32(OUT, chosen);
    for (int i = 0; i < MIPP_N_FLOAT32; i++)
        DOC_CHECK(OUT[i] == (A[i] < B[i] ? A[i] : B[i]));
}

/* §7.2: set_k */
static void set_k(void)
{
    /* --8<-- [start:set_k] */
    // In C: array of int32_t, one value per lane (MIPP_N_FLOAT32 lanes)
    int32_t mask_values[MIPP_N_FLOAT32];
    for (int i = 0; i < MIPP_N_FLOAT32; i++)
        mask_values[i] = (i % 3 == 0) ? 1 : 0; // lanes 0, 3, 6, ... active
    rvm_float32_t m = mipp_set_k_float32(mask_values);
    /* --8<-- [end:set_k] */
    int32_t act[DOC_BUF];
    lanes(m, act);
    for (int i = 0; i < MIPP_N_FLOAT32; i++)
        DOC_CHECK(act[i] == (i % 3 == 0));
}

/* §8.1: masks with LMUL = 2 */
static void lmul2(void)
{
    const float* ptr_a = A;
    const float* ptr_b = B;
    /* --8<-- [start:lmul2] */
    // C API: explicit multiplied types and identifiers
    rvd_float32_m2_t va = mipp_load_float32_m2(ptr_a);
    rvd_float32_m2_t vb = mipp_load_float32_m2(ptr_b);

    rvm_float32_m2_t m   = mipp_cmplt_float32_m2(va, vb);
    rvd_float32_m2_t res = mipp_add_float32_mask_m2(m, va, vb);
    /* --8<-- [end:lmul2] */
    mipp_storeu_float32_m2(OUT, res);
    for (int i = 0; i < MIPP_N_FLOAT32_M2; i++)
        DOC_CHECK(OUT[i] == (A[i] < B[i] ? A[i] + B[i] : A[i]));
}

int main(void)
{
    fill();
    variants();
    cast_k();
    tomsk();
    toreg();
    blend();
    set_k();
    lmul2();
    return doc_status();
}

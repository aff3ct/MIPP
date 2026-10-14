#include <stdint.h>
#include <mipp.h>

#include "doc_check.h"

#define SENTINEL (-1000.f)
#define LIMIT 150u /* masked gather / scatter: lanes with an index below LIMIT */

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float SRC[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF];
DOC_ALIGNED static float OUT2[DOC_BUF];
DOC_ALIGNED static float TABLE[DOC_BUF];
DOC_ALIGNED static uint32_t IDX[DOC_BUF];

static void fill(void)
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        SRC[i] = 100.f + (float)i;
        TABLE[i] = 0.5f * (float)i;
        IDX[i] = (uint32_t)((i * 7) % 300); /* distinct for the first 300 lanes */
        OUT[i] = OUT2[i] = SENTINEL;
    }
}

/* §2.1: aligned and unaligned accesses */
static void load_store(void)
{
    const float* ptr = A;      /* aligned */
    const float* uptr = A + 1; /* unaligned */
    float* out_ptr = OUT;      /* aligned */
    float* uout = OUT2 + 1;    /* unaligned */
    /* --8<-- [start:load_store] */
    rvd_float32_t a = mipp_load_float32(ptr);   // ptr aligned on MIPP_RVD_SIZE_BYTE
    rvd_float32_t b = mipp_loadu_float32(uptr); // any address

    mipp_store_float32(out_ptr, a);
    mipp_storeu_float32(uout, b);
    /* --8<-- [end:load_store] */
    for (int i = 0; i < MIPP_N_FLOAT32; i++) {
        DOC_CHECK(out_ptr[i] == A[i]);
        DOC_CHECK(uout[i] == A[i + 1]);
    }
}

/* §2.2: masked loads and stores */
static void masked(void)
{
    const float* ptr = A;
    const float* uptr = A + 1;
    float* out_ptr = OUT;
    float* uout = OUT2 + 1;
    for (int i = 0; i < DOC_BUF; i++) OUT[i] = OUT2[i] = SENTINEL;
    rvd_float32_t va = mipp_load_float32(A);
    rvd_float32_t vlimit = mipp_set1_float32(0.5f);
    rvd_float32_t v_src = mipp_load_float32(SRC);
    rvd_float32_m2_t wa = mipp_load_float32_m2(A);
    rvd_float32_m2_t wlimit = mipp_set1_float32_m2(0.5f);
    /* --8<-- [start:masked] */
    rvm_float32_t m = mipp_cmplt_float32(va, vlimit);

    rvd_float32_t v_z = mipp_load_float32_maskz(m, ptr);        // inactive lanes: 0
    rvd_float32_t v_s = mipp_load_float32_masks(m, v_src, ptr); // inactive lanes: v_src
    mipp_store_float32_mask(m, out_ptr, v_z);                   // inactive lanes: memory unchanged

    // LMUL = 2:
    rvm_float32_m2_t m2  = mipp_cmplt_float32_m2(wa, wlimit);
    rvd_float32_m2_t w_z = mipp_loadu_float32_maskz_m2(m2, uptr);
    mipp_storeu_float32_mask_m2(m2, uout, w_z);
    /* --8<-- [end:masked] */
    float s[DOC_BUF];
    mipp_storeu_float32(s, v_s);
    for (int i = 0; i < MIPP_N_FLOAT32; i++) {
        const int act = A[i] < 0.5f;
        DOC_CHECK(out_ptr[i] == (act ? A[i] : SENTINEL));
        DOC_CHECK(s[i] == (act ? A[i] : SRC[i]));
    }
    for (int i = 0; i < MIPP_N_FLOAT32_M2; i++)
        DOC_CHECK(uout[i] == (A[i] < 0.5f ? A[i + 1] : SENTINEL));
}

/* §3.1: gather */
static void gather(void)
{
    const uint32_t* idx_ptr = IDX;
    const float* table = TABLE;
    rvd_uint32_t vmax_idx = mipp_set1_uint32(LIMIT);
    /* --8<-- [start:gather] */
    rvd_uint32_t indices = mipp_load_uint32(idx_ptr);
    rvd_float32_t res = mipp_gather_float32_float32(table, indices);

    rvm_uint32_t m = mipp_cmplt_uint32(indices, vmax_idx);
    rvd_float32_t res_z = mipp_gather_float32_float32_maskz(m, table, indices);
    /* --8<-- [end:gather] */
    float r[DOC_BUF], z[DOC_BUF];
    mipp_storeu_float32(r, res);
    mipp_storeu_float32(z, res_z);
    for (int i = 0; i < MIPP_N_FLOAT32; i++) {
        DOC_CHECK(r[i] == TABLE[IDX[i]]);
        DOC_CHECK(z[i] == (IDX[i] < LIMIT ? TABLE[IDX[i]] : 0.f));
    }
}

/* §3.2: scatter */
static void scatter(void)
{
    const uint32_t* idx_ptr = IDX;
    float* out_table = OUT;
    for (int i = 0; i < DOC_BUF; i++) OUT[i] = SENTINEL;
    rvd_float32_t values = mipp_load_float32(A);
    rvd_uint32_t vmax_idx = mipp_set1_uint32(LIMIT);
    /* --8<-- [start:scatter] */
    rvd_uint32_t indices = mipp_load_uint32(idx_ptr);
    mipp_scatter_float32_float32(out_table, indices, values);

    rvm_uint32_t m = mipp_cmplt_uint32(indices, vmax_idx);
    mipp_scatter_float32_float32_mask(m, out_table, indices, values);
    /* --8<-- [end:scatter] */
    for (int i = 0; i < MIPP_N_FLOAT32; i++)
        DOC_CHECK(out_table[IDX[i]] == A[i]);
}

/* §4: element extraction */
static void extract(void)
{
    const float* ptr = A;
    /* --8<-- [start:extract] */
    rvd_float32_t v = mipp_load_float32(ptr);
    float32_t first_val = mipp_getfirst_float32(v);
    float32_t third_val = mipp_get_float32(v, 2);

    // LMUL = 2: idx goes up to MIPP_N_FLOAT32_M2 - 1
    rvd_float32_m2_t w = mipp_load_float32_m2(ptr);
    float32_t w_first = mipp_getfirst_float32_m2(w);
    float32_t w_last  = mipp_get_float32_m2(w, MIPP_N_FLOAT32_M2 - 1);
    /* --8<-- [end:extract] */
    DOC_CHECK(first_val == A[0]);
    DOC_CHECK(third_val == A[2]);
    DOC_CHECK(w_first == A[0]);
    DOC_CHECK(w_last == A[MIPP_N_FLOAT32_M2 - 1]);
}

int main(void)
{
    fill();
    load_store();
    masked();
    gather();
    scatter();
    extract();
    return doc_status();
}

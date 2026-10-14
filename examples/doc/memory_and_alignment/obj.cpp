#include <cstdint>
#include <mipp_obj.hpp>

#include "doc_check.h"

static const float SENTINEL = -1000.f;
static const uint32_t LIMIT = 150; // masked gather / scatter: lanes with an index below LIMIT

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float SRC[DOC_BUF];
DOC_ALIGNED static float OUT[DOC_BUF];
DOC_ALIGNED static float OUT2[DOC_BUF];
DOC_ALIGNED static float TABLE[DOC_BUF];
DOC_ALIGNED static uint32_t IDX[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        SRC[i] = 100.f + (float)i;
        TABLE[i] = 0.5f * (float)i;
        IDX[i] = (uint32_t)((i * 7) % 300); // distinct for the first 300 lanes
        OUT[i] = OUT2[i] = SENTINEL;
    }
}

// §2.1: aligned and unaligned accesses
static void load_store()
{
    const float* ptr = A;      // aligned
    const float* uptr = A + 1; // unaligned
    float* out_ptr = OUT;      // aligned
    float* uout = OUT2 + 1;    // unaligned
    // --8<-- [start:load_store]
    mipp::Rvd<float> a = mipp::load_obj<float>(ptr);   // ptr aligned on mipp::req_alignment()
    mipp::Rvd<float> b = mipp::loadu_obj<float>(uptr); // any address

    mipp::store(out_ptr, a);
    mipp::storeu(uout, b);
    // --8<-- [end:load_store]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++) {
        DOC_CHECK(out_ptr[i] == A[i]);
        DOC_CHECK(uout[i] == A[i + 1]);
    }
}

// §2.2: masked loads and stores
static void masked()
{
    const float* ptr = A;
    const float* uptr = A + 1;
    float* out_ptr = OUT;
    float* uout = OUT2 + 1;
    for (int i = 0; i < DOC_BUF; i++) OUT[i] = OUT2[i] = SENTINEL;
    mipp::Rvd<float> va = mipp::load_obj<float>(A);
    mipp::Rvd<float> vlimit = mipp::set1_obj<float>(0.5f);
    mipp::Rvd<float> v_src = mipp::load_obj<float>(SRC);
    mipp::Rvd<float, 2> wa = mipp::load_obj<float, 2>(A);
    mipp::Rvd<float, 2> wlimit = mipp::set1_obj<float, 2>(0.5f);
    // --8<-- [start:masked]
    mipp::Rvm<float> m = (va < vlimit);

    mipp::Rvd<float> v_z = mipp::load_obj<mipp::Z>(m, ptr);        // inactive lanes: 0
    mipp::Rvd<float> v_s = mipp::load_obj<mipp::S>(m, v_src, ptr); // inactive lanes: v_src
    mipp::store<mipp::M>(m, out_ptr, v_z);                          // inactive lanes: memory unchanged

    // LMUL = 2:
    mipp::Rvm<float, 2> m2  = (wa < wlimit);
    mipp::Rvd<float, 2> w_z = mipp::loadu_obj<mipp::Z>(m2, uptr);
    mipp::storeu<mipp::M>(m2, uout, w_z);
    // --8<-- [end:masked]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++) {
        const bool act = A[i] < 0.5f;
        DOC_CHECK(out_ptr[i] == (act ? A[i] : SENTINEL));
        DOC_CHECK(v_s[i] == (act ? A[i] : SRC[i]));
    }
    for (int i = 0; i < mipp::Rvd<float, 2>::N(); i++)
        DOC_CHECK(uout[i] == (A[i] < 0.5f ? A[i + 1] : SENTINEL));
}

// §3.1: gather
static void gather()
{
    const uint32_t* idx_ptr = IDX;
    const float* table = TABLE;
    mipp::Rvd<uint32_t> vmax_idx = mipp::set1_obj<uint32_t>(LIMIT);
    // --8<-- [start:gather]
    mipp::Rvd<uint32_t> indices = mipp::load_obj<uint32_t>(idx_ptr);
    mipp::Rvd<float> res = mipp::gather(table, indices);

    mipp::Rvm<uint32_t> m = (indices < vmax_idx);
    mipp::Rvd<float> res_z = mipp::gather<mipp::Z>(m, table, indices);
    // --8<-- [end:gather]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++) {
        DOC_CHECK(res[i] == TABLE[IDX[i]]);
        DOC_CHECK(res_z[i] == (IDX[i] < LIMIT ? TABLE[IDX[i]] : 0.f));
    }
}

// §3.2: scatter
static void scatter()
{
    const uint32_t* idx_ptr = IDX;
    float* out_table = OUT;
    for (int i = 0; i < DOC_BUF; i++) OUT[i] = SENTINEL;
    mipp::Rvd<float> values = mipp::load_obj<float>(A);
    mipp::Rvd<uint32_t> vmax_idx = mipp::set1_obj<uint32_t>(LIMIT);
    // --8<-- [start:scatter]
    mipp::Rvd<uint32_t> indices = mipp::load_obj<uint32_t>(idx_ptr);
    mipp::scatter(out_table, indices, values);

    mipp::Rvm<uint32_t> m = (indices < vmax_idx);
    mipp::scatter<mipp::M>(m, out_table, indices, values);
    // --8<-- [end:scatter]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++)
        DOC_CHECK(out_table[IDX[i]] == A[i]);
}

// §4: element extraction
static void extract()
{
    const float* ptr = A;
    // --8<-- [start:extract]
    mipp::Rvd<float> v = mipp::load_obj<float>(ptr);
    float first_val = mipp::getfirst(v);
    float third_val = v[2];

    // LMUL = 2: idx goes up to mipp::N<float, 2>() - 1
    mipp::Rvd<float, 2> w = mipp::load_obj<float, 2>(ptr);
    float w_first = mipp::getfirst(w);
    float w_last  = w[mipp::N<float, 2>() - 1];
    // --8<-- [end:extract]
    DOC_CHECK(first_val == A[0]);
    DOC_CHECK(third_val == A[2]);
    DOC_CHECK(w_first == A[0]);
    DOC_CHECK(w_last == A[mipp::N<float, 2>() - 1]);
}

int main()
{
    fill();
    load_store();
    masked();
    gather();
    scatter();
    extract();
    return doc_status();
}

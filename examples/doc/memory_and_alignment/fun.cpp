#include <cstdint>
#include <mipp.hpp>

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
    mipp::rvd<float> a = mipp::load<float>(ptr);   // ptr aligned on mipp::req_alignment()
    mipp::rvd<float> b = mipp::loadu<float>(uptr); // any address

    mipp::store(out_ptr, a);
    mipp::storeu(uout, b);
    // --8<-- [end:load_store]
    for (int i = 0; i < (int)mipp::N<float>(); i++) {
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
    mipp::rvd<float> va = mipp::load<float>(A);
    mipp::rvd<float> vlimit = mipp::set1<float>(0.5f);
    mipp::rvd<float> v_src = mipp::load<float>(SRC);
    mipp::rvd<float, 2> wa = mipp::load<float, 2>(A);
    mipp::rvd<float, 2> wlimit = mipp::set1<float, 2>(0.5f);
    // --8<-- [start:masked]
    mipp::rvm<float> m = mipp::cmplt(va, vlimit);

    mipp::rvd<float> v_z = mipp::load<mipp::Z>(m, ptr);        // inactive lanes: 0
    mipp::rvd<float> v_s = mipp::load<mipp::S>(m, v_src, ptr); // inactive lanes: v_src
    mipp::store<mipp::M>(m, out_ptr, v_z);                     // inactive lanes: memory unchanged

    // LMUL = 2:
    mipp::rvm<float, 2> m2  = mipp::cmplt(wa, wlimit);
    mipp::rvd<float, 2> w_z = mipp::loadu<mipp::Z, float, 2>(m2, uptr);
    mipp::storeu<mipp::M, float, 2>(m2, uout, w_z);
    // --8<-- [end:masked]
    float s[DOC_BUF];
    mipp::storeu(s, v_s);
    for (int i = 0; i < (int)mipp::N<float>(); i++) {
        const bool act = A[i] < 0.5f;
        DOC_CHECK(out_ptr[i] == (act ? A[i] : SENTINEL));
        DOC_CHECK(s[i] == (act ? A[i] : SRC[i]));
    }
    for (int i = 0; i < (int)mipp::N<float, 2>(); i++)
        DOC_CHECK(uout[i] == (A[i] < 0.5f ? A[i + 1] : SENTINEL));
}

// §3.1: gather
static void gather()
{
    const uint32_t* idx_ptr = IDX;
    const float* table = TABLE;
    mipp::rvd<uint32_t> vmax_idx = mipp::set1<uint32_t>(LIMIT);
    // --8<-- [start:gather]
    mipp::rvd<uint32_t> indices = mipp::load<uint32_t>(idx_ptr);
    mipp::rvd<float> res = mipp::gather(table, indices);

    mipp::rvm<uint32_t> m = mipp::cmplt(indices, vmax_idx);
    mipp::rvd<float> res_z = mipp::gather<mipp::Z, float, uint32_t>(m, table, indices);
    // --8<-- [end:gather]
    float r[DOC_BUF], z[DOC_BUF];
    mipp::storeu(r, res);
    mipp::storeu(z, res_z);
    for (int i = 0; i < (int)mipp::N<float>(); i++) {
        DOC_CHECK(r[i] == TABLE[IDX[i]]);
        DOC_CHECK(z[i] == (IDX[i] < LIMIT ? TABLE[IDX[i]] : 0.f));
    }
}

// §3.2: scatter
static void scatter()
{
    const uint32_t* idx_ptr = IDX;
    float* out_table = OUT;
    for (int i = 0; i < DOC_BUF; i++) OUT[i] = SENTINEL;
    mipp::rvd<float> values = mipp::load<float>(A);
    mipp::rvd<uint32_t> vmax_idx = mipp::set1<uint32_t>(LIMIT);
    // --8<-- [start:scatter]
    mipp::rvd<uint32_t> indices = mipp::load<uint32_t>(idx_ptr);
    mipp::scatter(out_table, indices, values);

    mipp::rvm<uint32_t> m = mipp::cmplt(indices, vmax_idx);
    mipp::scatter<mipp::M, float, uint32_t>(m, out_table, indices, values);
    // --8<-- [end:scatter]
    for (int i = 0; i < (int)mipp::N<float>(); i++)
        DOC_CHECK(out_table[IDX[i]] == A[i]);
}

// §4: element extraction
static void extract()
{
    const float* ptr = A;
    // --8<-- [start:extract]
    mipp::rvd<float> v = mipp::load<float>(ptr);
    float first_val = mipp::getfirst(v);
    float third_val = mipp::get(v, 2);

    // LMUL = 2: idx goes up to mipp::N<float, 2>() - 1
    mipp::rvd<float, 2> w = mipp::load<float, 2>(ptr);
    float w_first = mipp::getfirst(w);
    float w_last  = mipp::get(w, mipp::N<float, 2>() - 1);
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

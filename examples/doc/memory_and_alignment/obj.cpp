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
    // C++ Object API:
    mipp::Rvd<float> a = mipp::load_obj<float>(ptr);   // ptr aligned on mipp::req_alignment()
    mipp::Rvd<float> b = mipp::loadu_obj<float>(uptr); // any address
    mipp::Rvd<float> c(uptr);                          // the constructor performs an unaligned load

    mipp::store(out_ptr, a);
    mipp::storeu(uout, b + c);
    // --8<-- [end:load_store]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++) {
        DOC_CHECK(out_ptr[i] == A[i]);
        DOC_CHECK(uout[i] == 2.f * A[i + 1]);
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
    mipp::Rvd<float> oa(A), olimit = 0.5f, o_src(SRC);
    mipp::Rvd<float, 2> ow(A), owlimit = 0.5f;
    // --8<-- [start:masked]
    // C++ Object API (T and LMUL deduced from the Rvm mask):
    mipp::Rvm<float> m = (oa < olimit);

    mipp::Rvd<float> v_z = mipp::load_obj<mipp::Z>(m, ptr);
    mipp::Rvd<float> v_s = mipp::load_obj<mipp::S>(m, o_src, ptr);
    mipp::store<mipp::M>(m, out_ptr, v_z);

    mipp::Rvm<float, 2> m2 = (ow < owlimit);
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
    const uint32_t max_idx = LIMIT;
    // --8<-- [start:gather]
    // C++ Object API (T, the index type and LMUL deduced from the arguments):
    mipp::Rvd<uint32_t> indices(idx_ptr);
    mipp::Rvd<float> res = mipp::gather(table, indices);

    mipp::Rvm<uint32_t> m = (indices < max_idx);
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
    mipp::Rvd<float> o_values(A);
    const uint32_t max_idx = LIMIT;
    // --8<-- [start:scatter]
    // C++ Object API:
    mipp::Rvd<uint32_t> indices(idx_ptr);
    mipp::scatter(out_table, indices, o_values);

    mipp::Rvm<uint32_t> m = (indices < max_idx);
    mipp::scatter<mipp::M>(m, out_table, indices, o_values);
    // --8<-- [end:scatter]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++)
        DOC_CHECK(out_table[IDX[i]] == A[i]);
}

// §4: element extraction
static void extract()
{
    const float* ptr = A;
    const float limit = 0.5f;
    // --8<-- [start:extract]
    // C++ Object API:
    mipp::Rvd<float> v = mipp::load_obj<float>(ptr);
    float first_val = mipp::getfirst(v);
    float third_val = v[2];

    // LMUL = 2: idx goes up to mipp::N<float, 2>() - 1
    mipp::Rvd<float, 2> w = mipp::load_obj<float, 2>(ptr);
    float w_first = mipp::getfirst(w);
    float w_last  = w[mipp::N<float, 2>() - 1];

    // Mask lanes (bool, Object API only until the warning above is lifted):
    mipp::Rvm<float, 2> m = (w < limit);
    bool last_active = m[mipp::N<float, 2>() - 1];
    // --8<-- [end:extract]
    const int last = mipp::N<float, 2>() - 1;
    DOC_CHECK(first_val == A[0]);
    DOC_CHECK(third_val == A[2]);
    DOC_CHECK(w_first == A[0]);
    DOC_CHECK(w_last == A[last]);
    DOC_CHECK(last_active == (A[last] < limit));
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

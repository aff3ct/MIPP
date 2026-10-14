#include <cstdint>
#include <mipp_obj.hpp>

#include "doc_check.h"

DOC_ALIGNED static float A[DOC_BUF];
DOC_ALIGNED static float B[DOC_BUF];

static void fill()
{
    for (int i = 0; i < DOC_BUF; i++) {
        A[i] = (float)(i % 7) - 3.f;
        B[i] = (float)(i % 5) - 2.f;
    }
}

// §2.3: the four variants
static void variants()
{
    mipp::Rvd<float> va(A), vb(B);
    // --8<-- [start:variants]
    mipp::Rvm<float> m = (va > vb); // Mask produced by comparison operator
    mipp::Rvd<float> vsrc = 0.0f;

    // 1. Unmasked:
    auto res_u = mipp::add(va, vb);

    // 2. Merge-Masked: preserves va on false
    auto res_m = mipp::add<mipp::M>(m, va, vb);

    // 3. Zero-Masked: zeroes inactive elements on false
    auto res_z = mipp::add<mipp::Z>(m, va, vb);

    // 4. Source-Masked: preserves values from vsrc on false
    auto res_s = mipp::add<mipp::S>(m, vsrc, va, vb);
    // --8<-- [end:variants]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++) {
        const bool act = A[i] > B[i];
        DOC_CHECK(res_u[i] == A[i] + B[i]);
        DOC_CHECK(res_m[i] == (act ? A[i] + B[i] : A[i]));
        DOC_CHECK(res_z[i] == (act ? A[i] + B[i] : 0.f));
        DOC_CHECK(res_s[i] == (act ? A[i] + B[i] : 0.f));
    }
}

// §2.3: tip, concise mask syntax
static void using_m()
{
    mipp::Rvd<float> va(A), vb(B);
    mipp::Rvm<float> m = (va > vb);
    // --8<-- [start:using_m]
    using mipp::M;
    auto res = mipp::add<M>(m, va, vb);
    // --8<-- [end:using_m]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++)
        DOC_CHECK(res[i] == (A[i] > B[i] ? A[i] + B[i] : A[i]));
}

// §6.1: cast between mask types
static void cast_k()
{
    mipp::Rvd<float> oa(A), ob(B);
    // --8<-- [start:cast_k]
    // C++ Object API: target type as template argument (overloaded on Rvm and Rvd)
    mipp::Rvm<float> m_float = (oa < ob);
    mipp::Rvm<int32_t> m_int = mipp::cast<int32_t>(m_float);
    // --8<-- [end:cast_k]
    for (int i = 0; i < mipp::Rvm<int32_t>::N(); i++)
        DOC_CHECK(m_int[i] == (A[i] < B[i]));
}

// §6.4: blend
static void blend()
{
    mipp::Rvd<float> if_true(A), if_false(B);
    mipp::Rvm<float> m = (if_true < if_false);
    // --8<-- [start:blend]
    // C++ Object API: (mask, if_true, if_false)
    auto chosen_obj = mipp::blend(m, if_true, if_false);
    // --8<-- [end:blend]
    for (int i = 0; i < mipp::Rvd<float>::N(); i++)
        DOC_CHECK(chosen_obj[i] == (A[i] < B[i] ? A[i] : B[i]));
}

// §8.1: masks with LMUL = 2
static void lmul2()
{
    const float* ptr_a = A;
    const float* ptr_b = B;
    // --8<-- [start:lmul2]
    // C++ Object API: automatic LMUL and type deduction
    mipp::Rvd<float, 2> oa(ptr_a);
    mipp::Rvd<float, 2> ob(ptr_b);
    auto om = (oa < ob);                                // mipp::Rvm<float, 2>
    auto ores = mipp::add<mipp::M>(om, oa, ob);         // Deduces T=float and LMUL=2
    // --8<-- [end:lmul2]
    for (int i = 0; i < mipp::Rvd<float, 2>::N(); i++)
        DOC_CHECK(ores[i] == (A[i] < B[i] ? A[i] + B[i] : A[i]));
}

int main()
{
    fill();
    variants();
    using_m();
    cast_k();
    blend();
    lmul2();
    return doc_status();
}
